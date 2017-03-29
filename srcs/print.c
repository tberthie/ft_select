/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 23:36:42 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/30 00:51:26 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

#include "libft.h"

#include <term.h>

static void		collumn(t_select *select)
{
	select->col = (int)ft_parrlen((void**)select->list);
//	select->len = max (max strlen + tab // %4 == 0)
//	error ? select->col = 0
}

static void		allign(char *name, t_select *select)
{

}

void			print(t_select *select)
{
	int		pos;
	int		col;
	t_elem	*elem;

	tputs(tgetstr("cl", 0), 0, put_ret);
	collumn(select);
	pos = 0;
	while (pos < select->col)
	{
		col = 0;
		while (pos + col * select->col < (int)ft_parrlen((void**)select->list))
		{
			elem = select->list[pos + col * select->col];
			if (elem->selected)
				ft_printf(1, SELECTED);
			if (select->pos == pos + col * select->col)
				ft_printf(1, POSITION);
			ft_printf(1, "%s"NORMAL, elem->str);
			if (pos + ++col * select->col <
			(int)ft_parrlen((void**)select->list))
				allign(elem->str, select);
		}
		ft_printf(1, "\n");
		pos++;
	}
}
