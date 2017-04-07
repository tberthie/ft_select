/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:11:58 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/07 13:12:23 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

#include "libft.h"

#include <term.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>

static void		sigtstp(void)
{
	struct termios	term;
	char			sim[2];

	if (tcgetattr(0, &term) != -1)
	{
		sim[0] = (char)term.c_cc[VSUSP];
		sim[1] = 0;
		ioctl(0, TIOCSTI, sim);
	}
}

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
		signal(SIGCONT, handler);
		if (sig != SIGTSTP)
			exit(0);
		else
		{
			signal(SIGTSTP, SIG_DFL);
			sigtstp();
		}
	}
}

void			signals(void)
{
	int					i;

	i = 1;
	while (i < 32)
		signal(i++, handler);
}

void			signals_reset(void)
{
	int					i;

	i = 1;
	while (i < 32)
		signal(i++, handler);
}
