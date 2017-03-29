/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 20:35:12 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/30 00:47:10 by tberthie         ###   ########.fr       */
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

void				run(t_select *select);
char				config(t_select *select);
void				quit(t_select *select);
void				print(t_select *select);
int					put_ret(int c);

#endif
