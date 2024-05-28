NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread
INCLUDE = -I philo.h

SRCS = main.c

OBJ =			$(SRCS:%.c=%.o)

all: ${NAME}

srcs/%.o: srcs/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -O2 -c $< -o $(<:%.c=%.o)


$(NAME): $(OBJ)
	make -C ./mlx
	make all -C ./libft
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ) 

fclean: clean
	rm -f $(NAME) 
	
re:	fclean all

.PHONY: all clean fclean re
