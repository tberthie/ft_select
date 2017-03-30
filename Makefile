# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/20 22:18:00 by tberthie          #+#    #+#              #
#    Updated: 2017/03/30 15:12:05 by tberthie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS = $(addsuffix .o, $(addprefix objs/, main run print signal))

NAME = ft_select

all: objs $(NAME)

objs:
	mkdir objs

$(NAME): $(OBJS)
	make -C libft
	gcc -o $(NAME) $(OBJS) libft/libft.a -ltermcap

objs/%.o: srcs/%.c
	gcc -o $@ -c $< -I includes -I libft -Weverything

clean:
	rm -rf objs

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
