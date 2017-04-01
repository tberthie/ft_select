/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 23:36:42 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/01 19:05:30 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

#include "libft.h"

#include <term.h>
#include <sys/ioctl.h>

static void		collumn(void)
{
	struct winsize	ws;
	int				i;

	ioctl(0, TIOCGSIZE, &ws);
	g_select->len = 0;
	i = 0;
	while (g_select->list[i])
		if ((int)ft_strlen(g_select->list[i++]->str) > g_select->len)
			g_select->len = (int)ft_strlen(g_select->list[i - 1]->str);
	g_select->len += g_select->len % 4 ? 4 - g_select->len % 4 : 0;
	g_select->col = ws.ws_row ? ((int)ft_parrlen((void**)g_select->list) - 1) /
	ws.ws_row + 1 : 0;
	g_select->row = (int)ft_parrlen((void**)g_select->list) / g_select->col +
	((int)ft_parrlen((void**)g_select->list) % g_select->col ? 1 : 0);
	if (g_select->col * g_select->len + (g_select->col - 1) * 4 > ws.ws_col || 
	!g_select->col || !g_select->row)
	{
		g_select->row = 0;
		ft_printf(1, "ft_select: window too small\n");
	}
}

static void		align(int len)
{
	int		diff;

	diff = g_select->len - len;
	while (diff--)
		ft_printf(1, " ");
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
	while (pos < g_select->row)
	{
		col = 0;
		while (col < g_select->col && pos + col * g_select->row <
		(int)ft_parrlen((void**)g_select->list))
		{
			elem = g_select->list[pos + col * g_select->row];
			if (elem->selected)
				ft_printf(1, SELECTED);
			if (g_select->pos == pos + col * g_select->row)
				ft_printf(1, POSITION);
			ft_printf(1, "%s"NORMAL, elem->str);
			if (++col < g_select->col)
				align((int)ft_strlen(elem->str));
		}
		if (++pos < g_select->row)
			ft_printf(1, "\n");
	}
}
