NAME = minishell

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRCS = $(addprefix ./src/, testing.c)
SRCS_UTILS = $(addprefix ./src/utils/, command_spliter.c free_fts.c)

OBJS = $(addsuffix .o, $(notdir $(basename $(SRCS))))
OBJS_UTILS = $(addsuffix .o, $(notdir $(basename $(SRCS_UTILS))))

LIBFT = ./includes/libft_plus/libft.a
LIBFT_LINK = -L./includes/libft_plus -lft
FT_PRINTF_LINK = -L./includes/libft_plus/ft_printf -lftprintf

all:		$(NAME)

$(OBJS_UTILS):	$(SRCS_UTILS)
			@$(CC) $(CFLAGS) -c $(SRCS_UTILS)

$(OBJS):	$(SRCS)
			@$(CC) $(CFLAGS) -c $(SRCS)

$(NAME):	$(OBJS) $(OBJS_UTILS) $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJS) $(OBJS_UTILS) $(LIBFT_LINK) $(FT_PRINTF_LINK) -lreadline -o $(NAME)
			@echo "Minishell compiled!"

$(LIBFT):
			@make -C ./includes/libft_plus

clean:
			@rm -f $(OBJS) $(OBJS_UTILS)
			@make -C ./includes/libft_plus clean

fclean:		clean
			@rm -f $(NAME)
			@make -C ./includes/libft_plus fclean
			@echo "Everything cleaned!"

re:			fclean all

.PHONY: all, clean, fclean, re
