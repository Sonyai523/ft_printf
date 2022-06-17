# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rarthric <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/15 18:02:33 by rarthric          #+#    #+#              #
#    Updated: 2021/11/15 18:02:41 by rarthric         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c

OBJS = ${SRCS:.c=.o}


CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

HEADER = ft_printf.h

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -I./$(HEADER) -c $< -o $@

all:      ${NAME}

${NAME}: 	${OBJS}
			ar rc ${NAME} ${OBJS} $?
			ranlib ${NAME}

clean:
	${RM} ${OBJS}

fclean:       clean
	${RM} ${NAME}

re:          fclean all


.PHONY:       all clean fclean re
