/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 20:35:12 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/30 01:54:46 by tberthie         ###   ########.fr       */
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
	char		*term;

	t_elem		**list;
	int			pos;

	int			len;
	int			col;

	char		pad[4];
}					t_select;

extern t_select		*g_select;

void				run(void);
char				config(void);
void				quit(void);
void				print(void);
void				signals(void);
int					put_ret(int c);

#endif
