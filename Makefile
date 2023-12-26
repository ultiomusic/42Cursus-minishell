SRCS := main.c \
        parser.c \
        parser1.c \
        parsepushback.c \
        linked_list.c \
        list_function.c \
        heredocs.c \
        lexer.c \
        initbuiltin.c \
        free.c \
        expand3.c \
        expand2.c \
        expand1.c \
        expand.c  \
        error.c \
        new_bul/ft_cd.c \
        new_bul/ft_cd1.c \
        new_bul/ft_echo.c \
        new_bul/ft_unset.c \
        new_bul/ft_env.c \
        new_bul/ft_exit.c \
        new_bul/ft_export_utils.c \
        new_bul/ft_export.c \
        new_bul/ft_pwd.c \
        executor.c \
        executor_utils.c \
        executor_utils1.c \
        executor_utils2.c \
        executor_utils3.c \
        split_token.c \
        split_token2.c \
        split_token3.c

CC = @gcc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
LIBFT := libft/libft.a
RM = @rm -rf

OBJS = $(SRCS:.c=.o)

READLINE = readline

all: $(READLINE) $(NAME)

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=${PWD}/readline
	cd readline-8.2 && make install


$(NAME): $(LIBFT) $(OBJS)
	@echo "[COMPILING...]"
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LIBFT) -I${PWD}/readline/include/ -lreadline -L${PWD}/readline/lib  

$(LIBFT):
	make -C libft/

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/readline/include/

fclean: clean
	$(RM) $(NAME)
	make -C libft/ fclean
	@rm -rf readline-8.2 readline-8.2.tar.gz

clean:
	@echo "[DELETING...]"
	@$(RM) $(OBJS)
	@echo "[DELETED]"

re: fclean all

.PHONY: all fclean clean re