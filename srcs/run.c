/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 00:57:44 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/30 00:49:49 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

#include "libft.h"

#include <term.h>
#include <unistd.h>

static void		selection(t_select *select)
{
	t_elem	*elem;

	elem = select->list[select->pos];
	if (elem->selected)
		elem->selected = 0;
	else
		elem->selected = 1;
	print(select);
}

static void		remove(t_select *select)
{
	t_elem	*elem;

	elem = select->list[select->pos];
	ft_parrprem((void**)select->list, elem);
	if (select->pos >= (int)ft_parrlen((void**)select->list))
		select->pos = (int)ft_parrlen((void**)select->list) - 1;
	print(select);
}

static void		move(t_select *select, char key)
{
	if (key == 66)
	{
		if (++select->pos == (int)ft_parrlen((void**)select->list))
			select->pos = 0;
	}
	else if (key == 65)
	{
		if (--select->pos < 0)
			select->pos = (int)ft_parrlen((void**)select->list) - 1;
	}
	else if (key == 68)
	{
		if (select->pos - select->col >= 0)
			select->pos -= select->col;
	}
	else if (key == 67)
	{
		if (select->pos + select->col < (int)ft_parrlen((void**)select->list))
			select->pos += select->col;
	}
	print(select);
}

static void		output(t_select *select)
{
	while (*select->list)
	{
		if ((*select->list)->selected)
			ft_printf(1, "%s ", (*select->list)->str);
		select->list++;
	}
	ft_printf(1, "\n");
}

void			run(t_select *select)
{
	char	buf[4];
	int		rd;

	rd = 0;
	print(select);
	while (ft_parrlen((void**)select->list) &&
	(rd = (int)read(0, buf, 3)) != -1)
	{
		buf[rd] = 0;
		if (buf[0] == 32)
			selection(select);
		else if (buf[0] == 10 || (buf[0] == 27 && !buf[1]))
			break ;
		else if (buf[0] == 127 || buf[0] == 126)
			remove(select);
		else if (buf[0] == 27)
			move(select, buf[2]);
	}
	if (rd > 0 && buf[0] == 10)
		output(select);
	quit(select);
}
