# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 12:00:07 by dmaessen          #+#    #+#              #
#    Updated: 2023/07/12 17:53:53 by dmaessen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =  main.c init.c utils.c utils2.c utils3.c log_msg.c routine.c routine_alone.c control.c \

OBJ = ${SRC:.c=.o}

CC = cc 
CFLAGS = -Wall -Wextra -Werror -pthread -Ofast #-g -fsanitize=thread 
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean
	@$(MAKE) all

.PHONY:	all clean fclean re