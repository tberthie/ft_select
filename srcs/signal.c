/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:11:58 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/01 19:01:23 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

#include "libft.h"

#include <stdlib.h>
#include <signal.h>

static void		handler(int sig)
{
	if (sig == SIGWINCH || sig == SIGCONT)
	{
		if (sig == SIGCONT)
			config();
		print();
	}
	else
	{
		quit();
		if (sig != SIGTSTP)
			exit(0);
	}
}

void			signals(void)
{
	struct sigaction	*ac;
	int					i;

	ac = ft_memalloc(sizeof(struct sigaction));
	ac->sa_handler = handler;
	ac->sa_flags = SA_NODEFER;
	i = 0;
	while (i < 32)
		sigaction(i++, ac, 0);
	free(ac);
}

void			signals_reset(void)
{
	struct sigaction	*ac;
	int					i;

	ac = ft_memalloc(sizeof(struct sigaction));
	ac->sa_handler = SIG_DFL;
	i = 0;
	while (i < 32)
		sigaction(i++, ac, 0);
	free(ac);
}
