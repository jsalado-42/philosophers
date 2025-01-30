NAME=libft.a
AR=ar rcs
CFLAGS=-Wall -Werror -Wextra
RM=rm -f
INCLUDE=libft.h

FILES = ft_atoi.c \
		ft_itoa.c \
		ft_split.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_memcmp.c \
		ft_memchr.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strtrim.c \
		ft_strmapi.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		get_next_line.c \
		ft_printf_itoa.c \
		ft_printf_num.c \
		ft_printf_ptr.c \
		ft_printf_str.c \
		ft_printf_utils.c \
		ft_printf.c

BONUS_FILES = ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \

OBJS=$(FILES:.c=.o)
BONUS_OBJS=$(BONUS_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(BONUS_OBJS)
	@echo "Creating objects..."
	@ $(AR) $@ $?

%.o: %.c
	@ cc -c $(CFLAGS) $?

clean:
	@ $(RM) $(OBJS) $(BONUS_OBJS)
	@echo "Removed objects"

fclean: clean
	@ $(RM) $(NAME)
	@echo "Removed binary"

re: fclean all
	@echo "Finished Libft."

bonus: $(OBJS) $(BONUS_OBJS)
	$(AR) $(NAME) $(OBJS)

.PHONY: all clean fclean re bonus