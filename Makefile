define HEADER

                        MiniHell Compiled
                                by
                  (fmanzana && vde-prad) == true
 _______ _________ _       _________          _______  _        _
(       )\\__   __/( (    /|\\__   __/|\\     /|(  ____ \( \\      ( \\
| () () |   ) (   |  \\  ( |   ) (   | )   ( || (    \\/| (      | (
| || || |   | |   |   \\ | |   | |   | (___) || (__    | |      | |
| |(_)| |   | |   | (\\ \\) |   | |   |  ___  ||  __)   | |      | |
| |   | |   | |   | | \\   |   | |   | (   ) || (      | |      | |
| )   ( |___) (___| )  \\  |___) (___| )   ( || (____/\\| (____/\\| (____/\\
|/     \\|\\_______/|/    )_)\\_______/|/     \\|(_______/(_______/(_______/

endef
export HEADER

NAME = minishell

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
COLOR = \033[1;31m

SRCS = $(addprefix ./src/, minishell.c)
SRCS_UTILS = $(addprefix ./src/utils/, inputs_utils.c pipes_and_redirs.c qmarks_fts.c deep_spliter.c)
SRCS_FREE = $(addprefix ./src/utils/free_fts/, free_utils.c)
SRCS_TERMINATOR = $(addprefix ./src/terminator/, hd_utils.c init.c list.c utils.c redirections.c parserpath.c terminator.c signal.c)
SRCS_BUILTINS = $(addprefix ./src/terminator/builtins/, echo.c env.c pwd.c export.c unset.c exit.c cd.c)
SRCS_LIST = $(addprefix ./src/list/, list_filler.c list_moves.c iofiles_fdr.c iofiles_utils.c infiles_utils.c cmd_arrayer.c cmd_arrayer_utils.c parser.c)
SRCS_SYNTAX = $(addprefix ./src/syntax_errors/, syntax_checker.c)
SRCS_EXPAN = $(addprefix ./src/expander/, expander.c expander_utils.c)

OBJS = $(addsuffix .o, $(notdir $(basename $(SRCS))))
OBJS_UTILS = $(addsuffix .o, $(notdir $(basename $(SRCS_UTILS))))
OBJS_FREE = $(addsuffix .o, $(notdir $(basename $(SRCS_FREE))))
OBJS_TERMINATOR = $(addsuffix .o, $(notdir $(basename $(SRCS_TERMINATOR))))
OBJS_BUILTINS = $(addsuffix .o, $(notdir $(basename $(SRCS_BUILTINS))))
OBJS_LIST = $(addsuffix .o, $(notdir $(basename $(SRCS_LIST))))
OBJS_SYNTAX = $(addsuffix .o, $(notdir $(basename $(SRCS_SYNTAX))))
OBJS_EXPAN = $(addsuffix .o, $(notdir $(basename $(SRCS_EXPAN))))

LIBFT = ./includes/libft_plus/libft.a
LIBFT_LINK = -L./includes/libft_plus -lft
FT_PRINTF_LINK = -L./includes/libft_plus/ft_printf -lftprintf
RL_LIB = -I /Users/$(USER)/.brew/opt/readline/include
RL_LIB_LINK = -L /Users/$(USER)/.brew/opt/readline/lib -lreadline

all:		 $(NAME)

$(OBJS_TERMINATOR):	$(SRCS_TERMINATOR)
			@$(CC) $(CFLAGS) -c $(SRCS_TERMINATOR) $(RL_LIB)

$(OBJS_BUILTINS):	$(SRCS_BUILTINS)
			@$(CC) $(CFLAGS) -c $(SRCS_BUILTINS)

$(OBJS_LIST):	$(SRCS_LIST)
			@$(CC) $(CFLAGS) -c $(SRCS_LIST)

$(OBJS_UTILS):	$(SRCS_UTILS)
			@$(CC) $(CFLAGS) -c $(SRCS_UTILS)

$(OBJS_FREE):	$(SRCS_FREE)
			@$(CC) $(CFLAGS) -c $(SRCS_FREE)

$(OBJS_SYNTAX):	$(SRCS_SYNTAX)
			@$(CC) $(CFLAGS) -c $(SRCS_SYNTAX)

$(OBJS_EXPAN):	$(SRCS_EXPAN)
			@$(CC) $(CFLAGS) -c $(SRCS_EXPAN)

$(OBJS):	$(SRCS)
			@$(CC) $(CFLAGS) -c $(SRCS) $(RL_LIB)

$(NAME):	$(OBJS) $(OBJS_FREE) $(OBJS_UTILS) $(OBJS_LIST) $(OBJS_EXPAN) $(OBJS_SYNTAX) $(OBJS_TERMINATOR) $(OBJS_BUILTINS) $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJS) $(OBJS_FREE) $(OBJS_TERMINATOR) $(OBJS_EXPAN) $(OBJS_BUILTINS) $(OBJS_UTILS) $(OBJS_LIST) $(OBJS_SYNTAX) $(RL_LIB_LINK) $(LIBFT_LINK) $(FT_PRINTF_LINK) -o $(NAME)
			@echo "$(COLOR)$$HEADER"

$(LIBFT):
			@make -C ./includes/libft_plus

clean:
			@rm -f $(OBJS) $(OBJS_UTILS) $(OBJS_FREE) $(OBJS_LIST) $(OBJS_EXPAN) $(OBJS_SYNTAX) $(OBJS_BUILTINS) $(OBJS_TERMINATOR)
			@make -C ./includes/libft_plus clean

fclean:		clean
			@rm -f $(NAME)
			@make -C ./includes/libft_plus fclean
			@echo "Everything cleaned!"

re:			fclean all

.PHONY: all, clean, fclean, re, header
