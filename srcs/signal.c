/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 01:29:55 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/30 01:51:06 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

#include <signal.h>

static void		handler(int sig)
{
	if (sig == SIGWINCH)
		print();
}

void			signals(void)
{
	signal(SIGWINCH, handler);
}
