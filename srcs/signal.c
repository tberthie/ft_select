/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:11:58 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/15 13:27:41 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

#include "libft.h"

#include <term.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>

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
		if (sig != SIGTSTP || !isatty(1))
			exit(0);
		else
		{
			signal(SIGCONT, handler);
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
		signal(i++, SIG_DFL);
}
