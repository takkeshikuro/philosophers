NAME    = philo
CC 		= gcc
CFLAGS 	= -Wall -Werror -Wextra   -I /include/philo.h
SRCS 	= $(wildcard ./source/*.c ./include/philo.h) 
OBJS 	= $(SRCS:.c=.o)
OBJS_T	= $(wildcard ./source/*.o)
#-
NC		:= \033[m
B_RED	:= \033[1;31m
RED 	:= \033[0;31m
B_GREEN	:= \033[1;32m
GREEN 	:= \033[0;33m
B_BLUE 	:= \033[1;34m
BLUE 	:= \033[0;34m
PURPLE	:= \033[0;35m
WHCOLOR	:= \033[0;40m

all: $(NAME) 

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)  
	@$(CC) $(CFLAGS) $(OBJS) -o   $(NAME)
	@echo "$(B_BLUE) ~Compilation of philosophers:	\033[1;32mSUCCESS\033[m"

clean:
	@echo "$(GREEN)♻️ ${B_GREEN} .....TRASHING ALL OBJECTS..... $(GREEN)♻️ "
	@rm -f $(OBJS_T)
	@sleep 0.5
	@echo "$(B_RED)Done. $(NC)"

fclean: clean
	@rm -f $(NAME) 
	@echo "$(GREEN)♻️ ${B_GREEN} .....cleaning the rest.....  $(GREEN)♻️ "
	@echo "$(B_RED)Done. $(NC)"
	@echo "$(GREEN)♻️ ${B_GREEN} !TOUT PROPRE! $(GREEN)♻️ "
		
re: fclean all

.phony: all libft clean fclean
