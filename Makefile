NAME= minishell

CC= gcc

CFLAGS= -Wall -Wextra -Werror

CFILES = as_tree.c ft_environment.c expand.c loop.c tokenize.c minishell.c shared.c ft_lst_env.c\
		 pipe.c cd.c cmd_handler.c echo.c env.c export.c her_doc.c path.c pwd.c unset.c utils2.c utils1.c utils.c

OFILES = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))

OBJ_DIR = ./obj

SRC_DIR = ./src

LIBFT = libft/libft.a

INC= minishell.h

all: $(NAME)

$(NAME) : $(OBJ_DIR) $(OFILES) $(LIBFT)
	        @$(CC) $(OFILES) $(LIBFT) -L $(shell brew --prefix readline)/lib -lreadline -o  $(NAME)
		        @echo "minishell ok"

debug : $(OBJ_DIR) $(OFILES) $(LIBFT)
	        @$(CC) $(OFILES) $(LIBFT) -L $(shell brew --prefix readline)/lib -lreadline -fsanitize=address -o  $(NAME)
		        @echo "minishell ok"

$(OBJ_DIR):
	        @mkdir obj

$(OFILES): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC)
	        @$(CC) -c $(CFLAGS) -I $(shell brew --prefix readline)/include -c $< -o $@

$(LIBFT): force
	        @make -C libft
			@make bonus -C libft

force:

clean :
	        @rm -rf $(OBJ_DIR)
		        @make clean -C libft

fclean: clean
	        @rm -rf $(NAME)
		        @make fclean -C libft

re: fclean all
