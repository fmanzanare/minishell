NAME = minishell

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRCS = $(addprefix ./src/, )

OBJS = $(addsuffix .o, $(notdir $(basename $(SRCS))))

all:		$(NAME)

$(OBJS):	$(SRCS)
			@$(CC) $(CFLAGS) -c $(SRCS)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "Minishell compiled!"

clean:
			@rm -f $(OBJS)

fclean:		clean
			@rm -f $(NAME)
			@echo "Everything cleaned!"

re:			fclean all

.PHONY: all, clean, fclean, re
