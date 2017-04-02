/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 20:35:12 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/02 15:38:53 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H

# define NORMAL		"\x1b[0m"
# define POSITION	"\x1b[4m"
# define SELECTED	"\x1b[7m"

typedef struct		s_elem
{
	char		*str;
	char		selected;

	char		pad[7];
}					t_elem;

typedef struct		s_select
{
	unsigned long	config;
	char			*term;
	int				fd;
	char			pad[4];

	t_elem			**list;
	int				pos;

	int				len;
	int				col;
	int				row;
}					t_select;

extern t_select		*g_select;

void				run(void);
char				config(void);
void				quit(void);
void				print(void);
void				signals(void);
void				signals_reset(void);
int					put_ret(int c);

#endif
