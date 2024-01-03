/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:39:04 by baer              #+#    #+#             */
/*   Updated: 2024/01/02 21:57:39 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_simpleif(t_global *mini)
{
	if (mini->p_head->builtin && mini->p_head->builtin != &ft_echo
		&& mini->p_head->builtin != &ft_pwd)
	{
		mini->error = mini->p_head->builtin(mini, mini->p_head);
		return (0);
	}
	return (1);
}

int	ft_openpipe(t_proc *child, t_global *mini)
{
	if (pipe(child->fd) == -1)
	{
		perror("bash: ");
		mini->error = 1;
		return (0);
	}
	return (1);
}

void	setsingleio(t_proc *child, int *flag, t_global *mini, int *outfd)
{
	t_lexer	*red;
	t_lexer	*save;

	red = mini->p_head->redirections;
	while (red && red->next)
		red = red->next;
	save = red;
	if (child->pid == 0)
	{
		g_global.sig = 1;
		mini->error = 0;
		ft_setinput(&red, child, flag, mini);
		if ((*flag) == 1)
			dup2(child->fd[0], STDIN_FILENO);
		red = save;
		(*flag) = 0;
		ft_setoutput(&red, mini, flag, outfd);
		if ((*flag) == 1)
			dup2((*outfd), STDOUT_FILENO);
	}
}

void	ft_singleexecution(t_proc *child, t_global *mini, t_simple_cmds *cmd)
{
	if ((*child).pid == 0)
	{
		if (mini->error)
			exit(mini->error);
		if (cmd->builtin)
			exit(cmd->builtin(mini, cmd));
		execve(cmd->str[0], cmd->str, mini->env);
		write(2, "bash: ", 6);
		write(2, cmd->str[0], ft_strlen(cmd->str[0]));
		write(2, ": Command not found.\n", 22);
		exit(127);
	}
}

void	ft_closesinglepipes(t_proc *child, int *outfd)
{
	close(*outfd);
	close((*child).fd[0]);
	close((*child).fd[1]);
}
