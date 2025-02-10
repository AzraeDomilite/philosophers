NAME	= philo
CC		= gcc
CFLAGS	= -Werror -Wall -Wextra -pthread -g3
MODE	= none
ifeq ($(MODE), color)
	CFLAGS	+= -D COLOR_MODE=1
endif
ifeq ($(MODE), debug)
	CFLAGS	+= -fsanitize=thread -g3
endif

SRC_PATH = src/
OBJ_PATH = obj/

SRC		=	main.c \
			args_handler.c \
			monitor.c \
			time.c \
			philo.c \
			init_data.c \
			print_output.c \
			exit.c \
			start.c \
			utils.c \
			error_handling.c \
			init_philos.c
			
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INC		= -I ./includes/

RESET = \033[0m
GREEN = \033[1;32m
RED = \033[1;31m
BLUE = \033[1;34m
YELLOW = \033[1;33m
BLACK = \033[0;30m
WHITE = \033[1;37m
ORANGE = \033[0;33m
VIOLET = \033[0;35m
CYAN = \033[0;36m

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "$(GREEN)Compilation of philo successful! 🧠💭$(RESET)"
valgrind:
	valgrind --leak-check=full --log-file=valgrind.log --show-leak-kinds=all --track-fds=all --default-suppressions=yes ./$(NAME)
	#--gen-suppressions=all
clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(RED)Clean of philo successful 🧹$(RESET)"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
