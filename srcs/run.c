/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 00:57:44 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/30 01:51:10 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

#include "libft.h"

#include <term.h>
#include <unistd.h>

static void		selection(void)
{
	t_elem	*elem;

	elem = g_select->list[g_select->pos];
	if (elem->selected)
		elem->selected = 0;
	else
		elem->selected = 1;
	print();
}

static void		remove(void)
{
	t_elem	*elem;

	elem = g_select->list[g_select->pos];
	ft_parrprem((void**)g_select->list, elem);
	if (g_select->pos >= (int)ft_parrlen((void**)g_select->list))
		g_select->pos = (int)ft_parrlen((void**)g_select->list) - 1;
	print();
}

static void		move(char key)
{
	if (key == 66)
	{
		if (++g_select->pos == (int)ft_parrlen((void**)g_select->list))
			g_select->pos = 0;
	}
	else if (key == 65)
	{
		if (--g_select->pos < 0)
			g_select->pos = (int)ft_parrlen((void**)g_select->list) - 1;
	}
	else if (key == 68)
	{
		if (g_select->pos - g_select->col >= 0)
			g_select->pos -= g_select->col;
	}
	else if (key == 67)
	{
		if (g_select->pos + g_select->col <
		(int)ft_parrlen((void**)g_select->list))
			g_select->pos += g_select->col;
	}
	print();
}

static void		output(void)
{
	while (*g_select->list)
	{
		if ((*g_select->list)->selected)
			ft_printf(1, "%s ", (*g_select->list)->str);
		g_select->list++;
	}
	ft_printf(1, "\n");
}

void			run(void)
{
	char	buf[4];
	int		rd;

	rd = 0;
	print();
	while (ft_parrlen((void**)g_select->list) &&
	(rd = (int)read(0, buf, 3)) != -1)
	{
		buf[rd] = 0;
		if (buf[0] == 32)
			selection();
		else if (buf[0] == 10 || (buf[0] == 27 && !buf[1]))
			break ;
		else if (buf[0] == 127 || buf[0] == 126)
			remove();
		else if (buf[0] == 27)
			move(buf[2]);
	}
	if (rd > 0 && buf[0] == 10)
		output();
	quit();
}
