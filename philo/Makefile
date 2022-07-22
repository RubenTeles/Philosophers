# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rteles <rteles@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 15:25:06 by rteles            #+#    #+#              #
#    Updated: 2022/07/22 21:31:32 by rteles           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES	=	philo_init.c \
			philo_status.c \
			philo_utils.c \
			logic.c

OBJECTS	=	$(SOURCES:.c=.o)

NAME	= 	philo

HEADER	= 	philo.h

CLANG	=	clang

INCLUDE	=	-lpthread

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -fsanitize=thread

RM		=	rm -f

all: $(NAME)

$(NAME) : $(OBJECTS)
	$(CLANG) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJECTS)

%.o: %.c $(HEADER)
	$(CLANG) $(FLAGS) -c $<  -o $(<:.c=.o)

clean:
	$(RM) $(OBJECTS)
	
fclean: clean 
	$(RM) $(NAME)

re:		fclean $(NAME) 

.PHONY: $(NAME) all clean fclean re