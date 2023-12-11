# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdiabate <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 17:32:54 by sdiabate          #+#    #+#              #
#    Updated: 2023/12/07 17:33:08 by sdiabate         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = philo

SRCS = src/actions.c src/init.c src/philosophers.c src/simulation.c  src/utils.c

OBJS = ${SRCS:.c=.o}

HEADERS = philosophers.

CFLAGS = -g -Werror -Wall -Wextra

all:			${NAME}

$(NAME):		${OBJS}
						@cc ${OBJS} $(CFLAGS) -o $(NAME)
						@echo "\033[1;5mProgram is ready!\033[0m"

clean:
				@rm -f ${OBJS}

fclean:			clean
						@cd src && rm -f ${NAME}
						@rm -f ${NAME}
						@echo "\033[1mAll clean!\033[0m"

re: fclean all

.PHONY: all clean fclean re
