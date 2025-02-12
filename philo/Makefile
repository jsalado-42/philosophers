NAME=philo

CC=cc
CFLAGS=-Wall -Wextra -Werror -pthread -fsanitize=address -g3
RM=rm -f

SRC_PATH=./src/
OBJ_PATH=./objs/
LIB_PATH=./include/

FILES=	main.c \
		actions.c \
		checker.c \
		philosopher.c \
		utils.c \
		wait.c

SRC_FILES=$(addprefix $(SRC_PATH), $(FILES)) 

OBJ=$(FILES:.c=.o)
OBJ_FILES=$(addprefix $(OBJ_PATH), $(OBJ))

# --- RULES --- #

all: $(OBJ_PATH) $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME) $(INCS)
	@echo "Program '$(NAME)' compiled."

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

clean:
	@rm -f $(OBJ_PATH)*.o
	@echo "Objects deleted."

fclean: clean
	@rm -f $(NAME)
	@echo "Program deleted."

re: fclean all

.PHONY: all clean fclean re

# --- RUN --- #

run-inf: re
	./$(NAME) 2 800 200 200

run-ko: re
	./$(NAME) 3 300 200 200

# --- INTERNAL TOOLS --- #

debug: fclean $(OBJ_PATH) $(NAME)
	@make libft-re
	@g$(CC) -g $(CFLAGS) $(OBJ_FILES) -o $(NAME) $(INCS) 
	@echo "$(DETAIL)- Debug program ready -"

info:
	@echo "$(SUCCESS)It works!"
	@echo "$(WARNING)--- Rule not implemented ---"
	@echo "$(ERROR)Error."
	@echo "$(INFO)This message is info only."
	@echo "$(DETAIL)Use it to clarify the process."

# --- OTHER THINGS --- #

SLEEP=0.1
CLEAR="\033c"
MAGENTA=\033[35m
BRIGHT_YELLOW=\033[1;33m
CYAN=\033[36m
BLUE=\033[34m

party:
	@for i in $$(seq 1 1000); do \
		printf $(CLEAR); \
		echo "\n$(MAGENTA)♪┏(・o ･)┛♪"; \
		sleep $(SLEEP); \
		printf $(CLEAR); \
		echo "\n$(BRIGHT_YELLOW)♪┗(・Ó ･)┓♪"; \
		sleep $(SLEEP); \
		printf $(CLEAR); \
		echo "\n$(BLUE)♪┗(・Ò ･)┓♪"; \
		sleep $(SLEEP); \
		printf $(CLEAR); \
		echo "\n$(CYAN)♪┏(・o ･)┛♪"; \
		sleep $(SLEEP); \
	done