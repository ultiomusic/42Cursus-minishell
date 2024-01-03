/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiutils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:46:16 by beeligul          #+#    #+#             */
/*   Updated: 2024/01/02 21:58:36 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setio(t_proc **childs, int parsersize, int *fds)
{
	int	i;

	i = 0;
	while (i < parsersize)
	{
		if ((*childs)[i].pid == 0)
		{
			if (i != 0 || fds[2] == 1)
				fds[0] = (*childs)[i].fd[0];
			if (i < parsersize - 1 && !fds[3])
				fds[1] = (*childs)[i + 1].fd[1];
		}
		i++;
	}
}

void	ft_execution(t_proc **childs, t_simple_cmds **cmd, int *fds,
					t_global *mini)
{
	if (!ft_isparent((*childs), fds[4]))
	{
		if (fds[0] != STDIN_FILENO)
		{
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]);
		}
		if (fds[1] != STDOUT_FILENO)
		{
			dup2(fds[1], (STDOUT_FILENO));
			close(fds[1]);
		}
		if (mini->error)
			exit(mini->error);
		else if (mini->p_head->builtin == &ft_exit)
			exit(0);
		execve((*cmd)->str[0], (*cmd)->str, mini->env);
		write(2, "bash: ", 6);
		write(2, (*cmd)->str[0], ft_strlen((*cmd)->str[0]));
		write(2, ": Command not found.\n", 22);
		exit(127);
	}
}

void	ft_take_multiinput_from_file(char *str, t_proc *child, int flag, int i)
{
	int		fdfiledoc;
	int		fdheredoc;
	char	buffer;

	if (!flag)
	{
		fdfiledoc = open(str, O_RDWR, 0777);
		if (fdfiledoc < 0)
		{
			write(2, "bash:", 6);
			perror(str);
		}
		fdheredoc = child[i].fd[1];
		while (read(fdfiledoc, &buffer, 1) > 0)
		{
			if (!flag)
				write(fdheredoc, &buffer, 1);
		}
		close(fdfiledoc);
	}
}
