NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread
INCLUDE = -I philo.h

SRCS = main.c \
		init.c \
		time.c \
		utils.c \

OBJ =			$(SRCS:%.c=%.o)

all: ${NAME}

srcs/%.o: srcs/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -O2 -c $< -o $(<:%.c=%.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ) 

fclean: clean
	rm -f $(NAME) 
	
re:	fclean all

.PHONY: all clean fclean re
