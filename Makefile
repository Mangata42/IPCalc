# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/22 11:03:46 by nghaddar          #+#    #+#              #
#    Updated: 2024/11/25 10:37:32 by nghaddar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC= ./src/*.c
NAME= IPCalc
# FLAGS= -Wall -Wextra -Werror 

$(NAME):
	@gcc $(SRC) $(FLAGS) -o $(NAME)

clean:
	@rm -rf $(NAME)

re: clean all

all:$(NAME)

.PHONY: $(NAME) clean fclean re