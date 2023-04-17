NAME = minishell

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRCS = $(addprefix ./src/, testing.c)
SRCS_UTILS = $(addprefix ./src/utils/, free_fts.c command_spliter.c inputs_utils.c pipes_and_redirs.c qmarks_fts.c)
SRCS_TERMINATOR = $(addprefix ./src/terminator/, setdata.c parserpath.c pipex.c)
SRCS_LIST = $(addprefix ./src/list/, list_filler.c list_moves.c iofiles_fdr.c cmd_arrayer.c)
SRCS_SYNTAX = $(addprefix ./src/syntax_errors/, syntax_checker.c)

OBJS = $(addsuffix .o, $(notdir $(basename $(SRCS))))
OBJS_UTILS = $(addsuffix .o, $(notdir $(basename $(SRCS_UTILS))))
OBJS_TERMINATOR = $(addsuffix .o, $(notdir $(basename $(SRCS_TERMINATOR))))
OBJS_LIST = $(addsuffix .o, $(notdir $(basename $(SRCS_LIST))))
OBJS_SYNTAX = $(addsuffix .o, $(notdir $(basename $(SRCS_SYNTAX))))

LIBFT = ./includes/libft_plus/libft.a
LIBFT_LINK = -L./includes/libft_plus -lft
FT_PRINTF_LINK = -L./includes/libft_plus/ft_printf -lftprintf

all:		$(NAME)

$(OBJS_TERMINATOR):	$(SRCS_TERMINATOR)
			@$(CC) $(CFLAGS) -c $(SRCS_TERMINATOR)

$(OBJS_LIST):	$(SRCS_LIST)
			@$(CC) $(CFLAGS) -c $(SRCS_LIST)

$(OBJS_UTILS):	$(SRCS_UTILS)
			@$(CC) $(CFLAGS) -c $(SRCS_UTILS)

$(OBJS_SYNTAX):	$(SRCS_SYNTAX)
			@$(CC) $(CFLAGS) -c $(SRCS_SYNTAX)

$(OBJS):	$(SRCS)
			@$(CC) $(CFLAGS) -c $(SRCS)

$(NAME):	$(OBJS) $(OBJS_UTILS) $(OBJS_LIST) $(OBJS_SYNTAX) $(OBJS_TERMINATOR) $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJS) $(OBJS_TERMINATOR) $(OBJS_UTILS) $(OBJS_LIST) $(OBJS_SYNTAX) $(LIBFT_LINK) $(FT_PRINTF_LINK) -lreadline -o $(NAME)
			@echo "Minishell compiled!"

$(LIBFT):
			@make -C ./includes/libft_plus

clean:
			@rm -f $(OBJS) $(OBJS_UTILS) $(OBJS_LIST) $(OBJS_SYNTAX)
			@make -C ./includes/libft_plus clean

fclean:		clean
			@rm -f $(NAME)
			@make -C ./includes/libft_plus fclean
			@echo "Everything cleaned!"

re:			fclean all

.PHONY: all, clean, fclean, re
