/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 23:36:42 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/30 01:51:45 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

#include "libft.h"

#include <term.h>
#include <sys/ioctl.h>

static void		collumn(void)
{
	struct winsize	ws;

	ioctl(0, TIOCGSIZE, &ws);
	ft_printf(1, "%d %d\n", ws.ws_row, ws.ws_col);
	g_select->col = (int)ft_parrlen((void**)g_select->list);
//	g_select->len = max (max strlen + %4)
//	window too small ? g_select->col = 0
}

static void		align(int len)
{
	int		diff;
	int		tabs;

	diff = g_select->len - len;
	tabs = diff / 4;
	while (tabs--)
		ft_printf(1, "\t");
	if (diff % 4)
		ft_printf(1, "\t");
	ft_printf(1, "\t");
}

void			print(void)
{
	int		pos;
	int		col;
	t_elem	*elem;

	tputs(tgetstr("cl", 0), 0, put_ret);
	collumn();
	pos = 0;
	while (pos < g_select->col)
	{
		col = 0;
		while (pos + col * g_select->col <
		(int)ft_parrlen((void**)g_select->list))
		{
			elem = g_select->list[pos + col * g_select->col];
			if (elem->selected)
				ft_printf(1, SELECTED);
			if (g_select->pos == pos + col * g_select->col)
				ft_printf(1, POSITION);
			ft_printf(1, "%s"NORMAL, elem->str);
			if (pos + ++col * g_select->col <
			(int)ft_parrlen((void**)g_select->list))
				align((int)ft_strlen(elem->str));
		}
		ft_printf(1, "\n");
		pos++;
	}
}
