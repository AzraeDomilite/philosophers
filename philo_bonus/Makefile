NAME	= philo_bonus
CC		= gcc
CFLAGS	= -Werror -Wall -Wextra -pthread -g3
MODE	= none
ifeq ($(MODE), color)
	CFLAGS	+= -D COLOR_MODE=1
endif
ifeq ($(MODE), debug)
	CFLAGS	+= -fsanitize=thread -g
endif

SRC_PATH = src/
OBJ_PATH = obj/

SRC		=	main.c \
			args_handler.c \
			monitors.c \
			time.c \
			philo.c \
			init_monitor_sem.c \
			init_data.c \
			print_output.c \
			utils.c \
			utils2.c \
			error_handling.c \
			free.c \
			exit.c \
			one_philo.c \
			sem_names.c \
			philo_monitor.c \
			init_philo.c
			
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

.SILENT:

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "$(GREEN)Compilation of philo_bonus successful! 🧠💭$(RESET)"

valgrind:
	@if [ -z "$(ARGS)" ]; then \
		echo "$(RED)Usage: make valgrind ARGS=\"<number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\"$(RESET)"; \
	else \
		mkdir -p logs && \
		valgrind \
			--leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--track-fds=yes \
			--log-file=logs/valgrind_$(shell date +%H:%M:%S_%d_%m_%Y).log \
			./$(NAME) $(ARGS); \
	fi

clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(RED)Clean of philo_bonus successful 🧹$(RESET)"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
