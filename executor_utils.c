/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:15:58 by baer              #+#    #+#             */
/*   Updated: 2024/01/02 22:00:40 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_single_commands(t_global *mini)
{
	t_proc			child;
	int				out;
	int				outfd;
	int				flag;

	if (!ft_simpleif(mini))
		return (0);
	outfd = dup(STDOUT_FILENO);
	if (!ft_openpipe(&child, mini))
		return (0);
	if (mini->p_head->str[0])
		mini->p_head->str[0] = ft_set_path(mini, &(mini->p_head->str[0]));
	flag = 0;
	child.pid = fork();
	g_global.sig = 2;
	setsingleio(&child, &flag, mini, &outfd);
	close(outfd);
	close(child.fd[0]);
	close(child.fd[1]);
	ft_singleexecution(&child, mini, mini->p_head);
	waitpid(child.pid, &out, 0);
	ft_errorarranger(mini, out);
	return (0);
}

void	ft_take_input_from_terminal(char *str, t_proc *child, int flag)
{
	int		fdheredoc;
	char	*line;

	if (fork() == 0)
	{
		fdheredoc = (*child).fd[1];
		while (1)
		{
			line = readline("> ");
			if (ft_strcmp(line, str) == 0 || !line)
				break ;
			else if (!flag)
				ft_writeintoheredoc(fdheredoc, line);
			if (line)
				free(line);
		}
		close((*child).fd[1]);
		close((*child).fd[0]);
		exit(0);
	}
	else
		wait(NULL);
}

void	ft_writeintoheredoc(int fdheredoc, char *line)
{
	write(fdheredoc, line, ft_strlen(line));
	write(fdheredoc, "\n", 1);
}
