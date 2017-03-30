/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:11:58 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/30 15:36:16 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

#include <signal.h>

void			signals(void)
{
	signal(SIGWINCH, (void (*)(int))print);
	signal(SIGTSTP, (void (*)(int))quit);
}

void			signals_reset(void)
{
	signal(SIGWINCH, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}
