NAME= minishell

CC= gcc

CFLAGS= -Wall -Wextra -Werror

CFILES = astree.c astree_fill.c  env.c ft_environment.c utils.c ft_lst_env.c

OFILES = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))

OBJ_DIR = ./obj

SRC_DIR = ./src

LIBFT = libft/libft.a

INC= trees.h

all: $(NAME)

$(NAME) : $(OBJ_DIR) $(OFILES) $(LIBFT)
	        @$(CC) $(OFILES) $(LIBFT) -L readline/lib -lreadline -o $(NAME)
		        @echo "minishell ok"

$(OBJ_DIR):
	        @mkdir obj

$(OFILES): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC)
	        @$(CC) -c $(CFLAGS) -I readline/include -c $< -o $@

$(LIBFT): force
	        @make -C libft
	
force:

clean :
	        @rm -rf $(OBJ_DIR)
		        @make clean -C libft

fclean: clean
	        @rm -rf $(NAME)
		        @make fclean -C libft

re: fclean all
