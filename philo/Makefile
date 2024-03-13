# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/13 15:11:39 by aserebry          #+#    #+#              #
#    Updated: 2024/03/13 13:53:03 by aserebry         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= philo

SRCS 			= philosophers.c phil_lifecycle.c aux.c \
					monitor.c aux_lib.c

HEADER			= philosophers.h

OBJS 			= $(SRCS:.c=.o)
OBJS_BONUS 		= $(SRCS_BONUS:.c=.o)

# FLAGS 			= -Wextra -Werror -Wall
FLAGS 			= -Wextra -Werror -Wall -fsanitize=thread -g -O1



all: $(NAME)

$(OBJS): $(HEADER)

$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) -o $(NAME) 

%.o : %.c
	cc $(FLAGS) -c $<

$(OBJS_BONUS): $(HEADER_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	cc $(FLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all
