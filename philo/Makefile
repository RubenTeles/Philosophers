# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rteles <rteles@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 15:25:06 by rteles            #+#    #+#              #
#    Updated: 2022/06/30 19:16:08 by rteles           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES	=	philo.c

OBJECTS	=	$(SOURCES:.c=.o)

NAME	= 	philo

CC		=	gcc #-fsanitize=address

CFLAGS	=	-Wall -Wextra -Werror 

RM		=	rm -f

all: $(NAME)

$(NAME) : $(OBJECTS)

%.o: %.c
	@$(CC) -g $(CFLAGS) -c $< -o $@ -lpthread

clean:
	$(RM) $(OBJECTS)
	
fclean: clean 
	$(RM) $(NAME)

re:		fclean $(NAME) 

.PHONY: $(NAME) all clean fclean re