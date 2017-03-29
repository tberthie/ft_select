/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 20:34:49 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/30 00:27:27 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

#include "libft.h"

#include <term.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

int				put_ret(int c)
{
	write(1, &c, 1);
	return (1);
}

char			config(t_select *select)
{
	struct termios	term;

	if ((!select->term && !(select->term = getenv("TERM"))) ||
	tgetent(0, select->term) != 1 || tcgetattr(0, &term) == -1)
		return (0);
	term.c_lflag &= (unsigned long)~(ICANON | ECHO);
	tputs(tgetstr("vi", 0), 0, put_ret);
	return (tcsetattr(0, TCSANOW, &term) == -1) ? 0 : 1;
}

void			quit(t_select *select)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		ft_printf(2, "ft_select: failed to restore terminal configuration\n");
	term.c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, TCSANOW, &term) == -1)
		ft_printf(2, "ft_select: failed to restore terminal configuration\n");
	tputs(tgetstr("ve", 0), 0, put_ret);
}

int				main(int ac, char **av)
{
	t_select	*select;
	t_elem		**list;
	t_elem		*elem;

	select = (t_select*)ft_m(sizeof(t_select));
	select->term = 0;
	list = (t_elem**)ft_parrnew();
	if (ac-- < 2)
		ft_printf(2, "Usage: ft_select [...]\n");
	else
	{
		while (ac--)
		{
			elem = (t_elem*)ft_m(sizeof(t_elem));
			elem->selected = 0;
			elem->str = ft_strdup(*++av);
			ft_parrpush((void***)&list, elem);
		}
		select->list = list;
		select->pos = 0;
		if (!config(select))
			ft_printf(2, "ft_select: terminal configuration error\n");
		run(select);
	}
	return (0);
}