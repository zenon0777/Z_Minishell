#ifndef MINISHELL_H
#define MINISHELL_H

# include <sys/types.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/signal.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdbool.h>
# include <string.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"

# define SIG_INT 2
# define PIPE 0
# define CMD 2
# define RD 1

extern struct VAR
{
	int		id;
	pid_t	cpid;
	int		exit_status;
	char	*usr;
	int		i;
} var;

extern struct VAR var;

typedef struct fds
{
	int		in;
	int		out;
	int		*fd;
	int		flag;
}	t_fds;


typedef struct s_env{
	char			*key;
	char			*value;
	int				index;
	struct s_env	*next;

}	t_env;

typedef struct s_as
{
   char         *cmd;
   int		    type;
   struct s_as  *left;
   struct s_as  *right;
}   t_as;

void	ft_free(void **ptr);
bool	ft_isspace(int c);
// t_list	*ft_listnew(void *content);
// t_list	*ft_listlast(t_list *lst);
// void	ft_listdelone(t_list *lst, void (*del)(void*));
// void	ft_listclear(t_list **lst, void (*del)(void *));
size_t	ft_strlen(char const *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *string, int searchedChar);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_memset(void *s, int c, size_t n);
bool	ft_calloc0(void **ptr, size_t cnt, size_t n);
bool	ft_strappend(char **s, char *s2);
char	*expand_last(char *it);
void	expand_space(char *value, t_list **brace);
char	*expand_brace(t_list *brace);
char	*expand_middle(char *input, char *it, char *last, t_env *envmap);
char	*expand_internal(char *input, char *it, bool d_quote, t_env *envmap);
char	*expand(char *input, t_env *envmap, bool d_quote);
char	*tokenize_internal(char *input, char *begin, char *end, t_list **chunks);
void	tokenizer(char *input, t_list **chunks);
// void	ft_listadd_back(t_list **lst, t_list *new);
// t_env	*envirement(char *envp[]);
// t_env	*ft_listnew_edit(void *content, void *key);
// void	ft_putstr_fd(char *s, int fd);
// void	ft_putendl_fd(char *s, int fd);
// void	ft_putchar(char c, int fd);
void    loop(char *input, t_list *chunks, t_as *syntax, t_env *envmap);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *name, char *value);
char	*removeChar(char *str);
void	ft_while_env(t_env **env, char **envp, t_env **node, int *i);
t_env	*ft_environment(char **envp, t_env *env);
bool	set_rl(char *input, char *output, int fd, bool nl);
t_as	*ast_fill(t_list *lst, t_as *syntax);
t_as	*d_add_node(t_as *ast, t_as *node);
t_as	*d_new_node(char *str);
void	free_ast(t_as *ast);
int	check_ast(t_as *ast);
void	env_env(t_env *env);
//execution
void	cd_home(t_env *env);
int		ft_append(t_env **env, t_list *arg, t_env **lst);
void	ft_replace(t_env **env, t_list *arg, t_env **lst);
int		check_type(char *arg);
void	builting(t_env **env, t_list *arg);
void	one_cmd(t_env **env, t_list *arg, char **envp, char *str);
void	execute_one_cmd(char **cmd, t_env **env);
void	check_cmd(t_env **env, t_list *arg, t_fds *fd);
void	pwd_env(void);
char	*get_path(char *cmd, t_env **env);
char	**search_path(t_env **env, char	**paths);
void	unset_env(t_env **env, t_list *arg);
t_env	*unset(t_env *env, t_env *tmp, t_list *arg);
void	free_env(t_env *env);
void	ft_free_lst(t_list **head);
void	echo(t_list *arg);
char	*join_echo(t_list **arg);
void	echo_newline(char **s);
int		check_newline(char **str);
void	export_env(t_env **env, t_list *arg);
void	set_env_existed(t_env **env, t_list *arg, t_env **lst);
void	cd(t_env *env, t_list *arg);
t_env	*ft_lst_new1(char *key, char *value);
// t_list	*ft_lst_new_prime(char *str);
void	ft_lstadd_back_prime(t_env **lst, t_env *node);
char	*get_keys(char *str, int c);
void	env_env(t_env *env);
char	**env_str(t_env *env);
void	execute_pipe(t_env *env, t_list *arg, t_fds *fds, int i);
void	pipe_handler(t_fds *fds, t_list *arg, t_env *env, int i);
void	content_handler(t_list **arg, t_env **env, t_fds *fds);
void	execute_redir(t_list *arg, t_env **env, t_fds *fds, char *str);
char	*redirection_handler(t_list **arg, t_fds *fds, char *str);
void	input(t_list **arg, t_fds *fds);
void	output(t_list **arg, t_fds *fds);
void	execute(char **cmd, t_env **env, t_fds 	*fds);
int		her_doc(t_list *arg);
char	*get_next_line(int fd);
void	update_pwd(t_env **lst, char *home);
int		ft_multiple_check(char *arg);
void	ft_print_exported(t_env **env);
void	ft_add_export(char *key, char *value, t_env **env);
void	export_join(t_env **env, char *key, char *value);
void	ft_sort_env(t_env **env);
int		check_upper(char *str);
void	ft_free_2d(char **ptr);
#endif