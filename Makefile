NAME		= push_swap
CHECKER		= checker
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

COMMON		= fill_stack.c ft_split.c libft_function.c validate.c \
			  swap_push.c stack_rotate.c stack_reverse_rotate.c disorder_index.c
SRCS		= main.c parse_flags.c selection_sort.c  small_chunk_sort.c\
			  sort_three.c chunk_sort.c turk_sort_main.c turk_sort_calc.c turk_sort_operations.c \
			  bench.c bench_tools.c $(COMMON)
BONUS_SRCS	= checker.c get_next_line.c get_next_line_utils.c $(COMMON)

OBJS		= $(SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(CHECKER)

$(CHECKER): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(CHECKER)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(CHECKER)

re: fclean all

.PHONY: all bonus clean fclean re
