/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 23:36:42 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/30 00:33:25 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

#include "libft.h"

#include <term.h>

void			print(t_select *select)
{
	int		i;
	t_elem	*elem;

	tputs(tgetstr("cl", 0), 0, put_ret);
	i = 0;
	while (i < (int)ft_parrlen((void**)select->list))
	{
		elem = select->list[i];
		if (elem->selected && select->pos == i)
			ft_printf(1, SELPOS"%s", elem->str);
		else if (elem->selected)
			ft_printf(1, SELECTED"%s", elem->str);
		else if (select->pos == i)
			ft_printf(1, POSITION"%s", elem->str);
		else
			ft_printf(1, "%s", elem->str);
		ft_printf(1, NORMAL"\n");
		i++;
	}
}
