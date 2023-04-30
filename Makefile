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
CFLAGS = -Wall -Werror -Wextra
COLOR = \033[1;31m

SRCS = $(addprefix ./src/, testing.c)
SRCS_UTILS = $(addprefix ./src/utils/, free_fts.c command_spliter.c inputs_utils.c pipes_and_redirs.c qmarks_fts.c)
SRCS_TERMINATOR = $(addprefix ./src/terminator/, utils.c redirections.c parserpath.c terminator.c signal.c)
SRCS_BUILTINS = $(addprefix ./src/terminator/builtins/, echo.c env.c pwd.c)
SRCS_LIST = $(addprefix ./src/list/, list_filler.c list_moves.c iofiles_fdr.c cmd_arrayer.c)
SRCS_SYNTAX = $(addprefix ./src/syntax_errors/, syntax_checker.c)

OBJS = $(addsuffix .o, $(notdir $(basename $(SRCS))))
OBJS_UTILS = $(addsuffix .o, $(notdir $(basename $(SRCS_UTILS))))
OBJS_TERMINATOR = $(addsuffix .o, $(notdir $(basename $(SRCS_TERMINATOR))))
OBJS_BUILTINS = $(addsuffix .o, $(notdir $(basename $(SRCS_BUILTINS))))
OBJS_LIST = $(addsuffix .o, $(notdir $(basename $(SRCS_LIST))))
OBJS_SYNTAX = $(addsuffix .o, $(notdir $(basename $(SRCS_SYNTAX))))

LIBFT = ./includes/libft_plus/libft.a
LIBFT_LINK = -L./includes/libft_plus -lft
FT_PRINTF_LINK = -L./includes/libft_plus/ft_printf -lftprintf
RL_LIB = -I /Users/vde-prad/.brew/opt/readline/include
RL_LIB_LINK = -L /Users/vde-prad/.brew/opt/readline/lib -lreadline

all:		 $(NAME)

$(OBJS_TERMINATOR):	$(SRCS_TERMINATOR)
			@$(CC) $(CFLAGS) -c $(SRCS_TERMINATOR) $(RL_LIB)

$(OBJS_BUILTINS):	$(SRCS_BUILTINS) 
			@$(CC) $(CFLAGS) -c $(SRCS_BUILTINS)

$(OBJS_LIST):	$(SRCS_LIST)
			@$(CC) $(CFLAGS) -c $(SRCS_LIST)

$(OBJS_UTILS):	$(SRCS_UTILS)
			@$(CC) $(CFLAGS) -c $(SRCS_UTILS)

$(OBJS_SYNTAX):	$(SRCS_SYNTAX)
			@$(CC) $(CFLAGS) -c $(SRCS_SYNTAX)

$(OBJS):	$(SRCS)
			@$(CC) $(CFLAGS) -c $(SRCS) $(RL_LIB)

$(NAME):	$(OBJS) $(OBJS_UTILS) $(OBJS_LIST) $(OBJS_SYNTAX) $(OBJS_TERMINATOR) $(OBJS_BUILTINS) $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJS) $(OBJS_TERMINATOR) $(OBJS_BUILTINS) $(OBJS_UTILS) $(OBJS_LIST) $(OBJS_SYNTAX) $(RL_LIB_LINK) $(LIBFT_LINK) $(FT_PRINTF_LINK) -o $(NAME)
			@echo "$(COLOR)$$HEADER"

$(LIBFT):
			@make -C ./includes/libft_plus

clean:
			@rm -f $(OBJS) $(OBJS_UTILS) $(OBJS_LIST) $(OBJS_SYNTAX) $(OBJS_TERMINATOR)
			@make -C ./includes/libft_plus clean

fclean:		clean
			@rm -f $(NAME)
			@make -C ./includes/libft_plus fclean
			@echo "Everything cleaned!"

re:			fclean all

.PHONY: all, clean, fclean, re, header
