NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror 

SRC = *.c\
	libft/*.c
	
all : $(NAME)

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) -g
clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME) 
re:	fclean all