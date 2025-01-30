NAME=philosophers

CC=cc
CFLAGS=-Wall -Wextra -Werror
RM=rm -f

SRC_PATH=./src
OBJ_PATH=./objs/
LIB_PATH=./include/

LFT=libft
LFT_DIR=$(LIB_PATH)$(LFT)
LFT_LIB=$(LFT_DIR)/$(LFT).a

INCS=-I$(LFT_DIR)

FILES=main.c
SRC_FILES=$(addprefix $(SRC_PATH), $(FILES)) 

OBJ=$(FILES:.c=.o)
OBJ_FILES=$(addprefix $(OBJ_PATH), $(OBJ))

# --- RULES --- #

all: $(OBJ_PATH) $(LFT_LIB) $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME) $(LFT_LIB) $(INCS)
	@echo "Program '$(NAME)' compiled."

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

clean: libft-clean
	@rm -f $(OBJ_PATH)*.o
	@echo "Objects deleted."

fclean: libft-fclean clean
	@rm -f $(NAME)
	@echo "Program deleted."

re: fclean all

# --- INTERNAL TOOLS --- #

debug: fclean
	@make libft-re
	@$(CC) -g $(CFLAGS) $(FILES) -o $(NAME) $(LIBFT-DIR)/libft.a
	@echo "$(DETAIL)- Debug program ready -"

info:
	@echo "$(SUCCESS)It works!"
	@echo "$(WARNING)--- Rule not implemented ---"
	@echo "$(ERROR)Error."
	@echo "$(INFO)This message is info only."
	@echo "$(DETAIL)Use it to clarify the process."

# --- LIBFT --- #

$(LFT_LIB):
	@make all -C $(LFT_DIR)

libft-re: libft-fclean libft-all
	@make re -C $(LFT_DIR)

libft-clean:
	@make clean -C $(LFT_DIR)
	@echo "Libft deleted."

libft-fclean:
	@make fclean -C $(LFT_DIR)

libft-all:
	@make all -C $(LFT_DIR)

libft-c:
	@make clean -C $(LIBFT-DIR)

libft-fc:
	@make fclean -C $(LIBFT-DIR)

libft-re:
	@make re -C $(LIBFT-DIR)

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