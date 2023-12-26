/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:52:25 by ohayek            #+#    #+#             */
/*   Updated: 2023/12/25 19:48:10 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_globals g_global;

// static void	suppress_output(void)
// {
// 	struct termios	termios_p;

// 	if (tcgetattr(0, &termios_p) != 0)
// 		perror("Minishell: tcgetattr");
// 	termios_p.c_lflag &= ~ECHOCTL;
// 	if (tcsetattr(0, 0, &termios_p) != 0)
// 		perror("Minishell: tcsetattr");
// }

// void	ft_handler(int sig)
// {
// 	if (g_global.test2)
// 	{
// 		ft_putstr_fd("\n", 2);
// 		rl_on_new_line();
// 		return ;
// 	}
// 	ioctl(STDIN_FILENO, TIOCSTI, "\n");
// 	write(1, "\033[A", 3);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

void minishell_loop(char *line, t_global *mini)
{
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			exit(1);
		if (line[0])
			add_history(line);
		ft_init_lexer(mini, line);
		if (ft_check_error(mini))
		{
			ft_deallocate_lexer(mini);
			free(line);
			continue;
		}
		ft_expand(mini);
		ft_init_parser(mini);
		ft_executer(mini);
		ft_deallocate_all(mini);
		free(line);
	}
}

// void	sigquit_handler(int sig)
// {
// 	(void)sig;
// 	rl_redisplay();
// 	return ;
// }

static void suppress_output(void)
{
	struct termios termios_p;

	if (tcgetattr(0, &termios_p) != 0)
		perror("Minishell: tcgetattr");
	termios_p.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_p) != 0)
		perror("Minishell: tcsetattr");
}

static void handle_sigint(int sig)
{
	(void)sig;
	if (g_global.sig == 0)
	{
		write(1, "\n", 1);
		if(g_global.sig != 2)
			rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_global.sig == 1)
	{
		exit(1);
	}
}

static void handle_sigquit(int sig)
{
	(void)sig;
	rl_redisplay();
}

void signals_init(void)
{
	suppress_output();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
int main(int ac, char **av, char **ev)
{
	char *line;
	t_global mini;

	if (ac > 1)
		exit(1);
	line = NULL;
	(void)av;
	g_global.sig = 0;
	g_global.error_num = 0;
	mini.env = ft_setenv(ev);
	mini.export = ft_setenv(ev);
	mini.head = NULL;
	mini.p_head = NULL;
	signals_init();
	minishell_loop(line, &mini);
	return (0);
}
