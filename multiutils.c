/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:52:07 by baer              #+#    #+#             */
/*   Updated: 2024/01/02 21:53:44 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipecreation(t_global *mini, t_proc	**childs, int *parsersize)
{
	int	i;

	(void)mini;
	i = 0;
	while (i < (*parsersize))
	{
		if ((pipe((*childs)[i].fd)) == -1)
		{
			perror("bash: ");
			mini->error = 1;
			return (1);
		}
		(*childs)[i].pid = 1;
		i++;
	}
	return (0);
}

void	ft_setprocesses(t_global *mini, t_simple_cmds **cmd, t_proc **childs,
						int *parsersize)
{
	int	i;

	i = 0;
	while (i < *parsersize)
	{
		if (ft_isparent((*childs), *parsersize))
			(*childs)[i].pid = fork();
		if ((*childs)[i].pid == 0)
		{
			(*childs)[i].parsersize = *parsersize;
			(*cmd) = ft_find_parser_index(i, mini->p_head);
			(*cmd)->str[0] = ft_set_path(mini, &((*cmd)->str[0]));
			mini->error = 0;
		}
		i++;
	}
}

void	ft_closepipes(int parsersize, int outfd, int infd, t_proc **childs)
{
	int	i;

	i = 0;
	while (i < parsersize)
	{
		if (outfd != (*childs)[i].fd[1])
			close((*childs)[i].fd[1]);
		if (infd != (*childs)[i].fd[0])
			close((*childs)[i].fd[0]);
		i++;
	}
}

void	ft_waitmain(t_proc **childs, int parsersize, int *out)
{
	int	i;

	i = 0;
	if (ft_isparent((*childs), parsersize))
	{
		while (i < parsersize)
		{
			waitpid((*childs)[i].pid, out, 0);
			i++;
		}
		i = 0;
	}
	free((*childs));
}

void	ft_pipearrange(t_proc **childs, int *fds, t_global *mini,
						t_simple_cmds **cmd)
{
	int		i;
	int		parsersize;
	t_lexer	*red;
	t_lexer	*save;

	i = 0;
	parsersize = (*childs)[0].parsersize;
	while (i < parsersize)
	{
		if ((*childs)[i].pid == 0)
		{
			fds[2] = 0;
			red = (*cmd)->redirections;
			while (red && red->next)
				red = red->next;
			save = red;
			ft_setmultiinput(red, (*childs), &fds[2], i);
			red = save;
			fds[3] = 0;
			ft_setoutput(&red, mini, &fds[3], &fds[1]);
		}
		i++;
	}
}
