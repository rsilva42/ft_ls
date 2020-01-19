# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsilva <rsilva@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/10 23:44:31 by rsilva            #+#    #+#              #
#    Updated: 2018/07/22 05:30:08 by rsilva           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CCFLAGS = -c -Wall -Wextra -Werror
SRCS = sources/ft_ls.c sources/helpers.c sources/sorting.c sources/chkdsk_but_for_directories.c sources/errors.c sources/flags.c sources/print_longformat.c sources/helpers_two.c sources/uncapture.c
OBJS = objects/ft_ls.o objects/helpers.o objects/sorting.o objects/chkdsk_but_for_directories.o objects/errors.o objects/flags.o objects/print_longformat.o objects/helpers_two.o objects/uncapture.o
INCLS = includes

all: $(NAME)

objects/%.o: sources/%.c
	@/bin/mkdir -p objects
	gcc $(CCFLAGS) -I$(INCLS) $< -o $@

$(NAME): $(OBJS)
	gcc $(OBJS) -o $(NAME)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
