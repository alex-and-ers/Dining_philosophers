# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/13 15:12:29 by aserebry          #+#    #+#              #
#    Updated: 2024/01/26 16:30:55 by aserebry         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			= philo_bonus

SRCS			= philosophers_bonus.c phil_life_bon.c \
				aux_bon.c aux_lib_bon.c

HEADER			= philosophers_bonus.h

OBJS			= $(SRCS:.c=.o)

FLAGS 			= -Wextra -Werror -Wall


all: $(NAME)

$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) -o $(NAME) 

%.o : %.c
	cc $(FLAGS) -c $<

$(OBJS): $(HEADER)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean $(NAME_BONUS)