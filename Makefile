# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 12:40:58 by mkokorev          #+#    #+#              #
#    Updated: 2024/10/03 11:46:29 by mkokorev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
SRC		= forks.c parce.c Philo.c simulation.c threads.c time.c ./utils/atoi.c ./utils/free.c \
		  ./utils/mutex.c ./utils/utils.c

OBJ		= $(SRC:.c=.o)
CFLAGS	= -Wall -Wextra -Werror -pthread
CC		= cc

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
