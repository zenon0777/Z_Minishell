#include "../minishell.h"

struct VAR	var;
void	new_prompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	back_slash(int sig)
{
	printf("Quit\n");
	(void)sig;
}

void sign_handler(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, new_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	// if (sig == 3)
	// {
	// 	printf("exit\n");
	// 	exit(0);
	// }
	
}

int main(int argc, char const *argv[], char *envp[])
{
	t_env	*envmap = NULL;
	t_list	*chunks = NULL;
	t_as	*syntax = NULL;
	char	*input = NULL;

	(void)argv;
	if (argc == 1)
	{
		envmap = ft_environment(envp, envmap);
		//signal(SIG_INT, sign_handler);
		// rl_catch_signals = 0;
		loop(input, chunks, syntax, envmap);
		return 0;
	}
}
