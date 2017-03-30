/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:11:58 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/30 20:34:36 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

#include <signal.h>

static void		handler(int sig)
{
	ft_printf(2, "Signal %d\n", sig);
	if (sig == SIGWINCH || sig == SIGCONT)
	{
		if (sig == SIGCONT)
			config();
		print();
	}
	else
	{
		quit();
		exit(0);
	}
}

void			signals(void)
{
	int			i;

	i = 0;
	while (i < 32)
		signal(i++, handler);
}

void			signals_reset(void)
{
	int			i;

	i = 0;
	while (i < 32)
		signal(i++, SIG_DFL);
}
