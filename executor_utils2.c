/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:15:58 by baer              #+#    #+#             */
/*   Updated: 2024/01/04 16:32:37 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_multiple_commands(t_global *mini)
{
	t_proc			*childs;
	t_simple_cmds	*cmd;
	int				out;
	int				parsersize;
	int				fds[5];

	fds[1] = STDOUT_FILENO;
	fds[0] = STDIN_FILENO;
	fds[2] = 0;
	fds[3] = 0;
	cmd = mini->p_head;
	parsersize = ft_parsersize(cmd);
	fds[4] = parsersize;
	childs = (t_proc *)malloc(sizeof(t_proc) * (parsersize));
	if (ft_pipecreation(mini, &childs, &parsersize))
		return (0);
	ft_setprocesses(mini, &cmd, &childs, &parsersize);
	ft_pipearrange(&childs, fds, mini, &cmd);
	ft_setio(&childs, parsersize, fds);
	ft_closepipes(parsersize, fds[1], fds[0], &childs);
	ft_execution(&childs, &cmd, fds, mini);
	ft_waitmain(&childs, parsersize, &out);
	if (WIFEXITED(out))
		mini->error = WEXITSTATUS(out);
	return (0);
}

int	ft_isparent(t_proc *childs, int parsersize)
{
	int	i;

	i = 0;
	while (i < parsersize)
	{
		if (childs[i].pid == 0)
			return (0);
		i++;
	}
	return (1);
}

t_simple_cmds	*ft_find_parser_index(int i, t_simple_cmds *parser)
{
	int	j;

	j = 0;
	while (j < i)
	{
		parser = parser->next;
		j++;
	}
	return (parser);
}

char	*ft_set_path(t_global *mini, char **str)
{
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	path = ft_findinenv(mini, "PATH");
	if (ft_strcmp(path, "Yok") == 0)
		return (*str);
	paths = ft_split(path, ":");
	free(path);
	while (paths[i])
	{
		path = ft_path_arrange(paths[i++], (*str));
		if (!access(path, F_OK))
		{
			free(*str);
			ft_freearr(&paths);
			return (path);
		}
		free(path);
	}
	ft_freearr(&paths);
	return (*str);
}

char	*ft_path_arrange(char *path, char *str)
{
	char	*buffer;
	char	*save;

	if (path[ft_strlen(path) - 1] == '/')
		return (ft_strjoin(path, str));
	else
	{
		buffer = ft_strjoin(path, "/");
		save = buffer;
		buffer = ft_strjoin(buffer, str);
		free(save);
		return (buffer);
	}
}
