/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 20:34:49 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/02 15:21:47 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

#include "libft.h"

#include <term.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

t_select		*g_select = 0;

int				put_ret(int c)
{
	write(g_select->fd, &c, 1);
	return (1);
}

char			config(void)
{
	struct termios	term;
	int				fd;

	signals();
	if ((!g_select->term && !(g_select->term = getenv("TERM"))) ||
	tgetent(0, g_select->term) != 1 || tcgetattr(0, &term) == -1)
		return (0);
	g_select->config = term.c_lflag;
	term.c_lflag &= (unsigned long)~(ICANON | ECHO) | ISIG;
	if ((fd = open("/dev/tty", O_WRONLY)) < 0)
		return (0);
	g_select->fd = fd;
	tputs(tgetstr("vi", 0), 0, put_ret);
	return (tcsetattr(0, TCSANOW, &term) == -1) ? 0 : 1;
}

void			quit(void)
{
	struct termios	term;

	signals_reset();
	if (tcgetattr(0, &term) == -1)
		ft_printf(2, "ft_select: failed to restore terminal configuration\n");
	term.c_lflag &= g_select->config;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		ft_printf(2, "ft_select: failed to restore terminal configuration\n");
	tputs(tgetstr("ve", 0), 0, put_ret);
	tputs(tgetstr("cl", 0), 0, put_ret);
}

static void		output(void)
{
	char		**out;
	int			i;

	out = (char**)ft_parrnew();
	while (*g_select->list)
	{
		if ((*g_select->list)->selected)
			ft_parrpush((void***)&out, (*g_select->list)->str);
		g_select->list++;
	}
	i = 0;
	while (out[i])
	{
		out[i + 1] ? ft_printf(1, "%s ", out[i]) : ft_printf(1, out[i]);
		i++;
	}
	ft_parrfree((void**)out);
}

int				main(int ac, char **av)
{
	t_elem		**list;
	t_elem		*elem;

	g_select = (t_select*)ft_m(sizeof(t_select));
	g_select->term = 0;
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
		g_select->list = list;
		g_select->pos = 0;
		config() ? run() : ft_printf(2,
		"ft_select: terminal configuration error\n");
		quit();
		output();
	}
	return (0);
}
