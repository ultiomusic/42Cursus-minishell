/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:10:29 by beeligul          #+#    #+#             */
/*   Updated: 2023/12/23 19:20:52 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_findinenv(t_global *mini, char *str)
{
	char	*save;
	char	*fre;
	int		i;

	i = 0;
	save = ft_strjoin(str, "=");
	while (mini->env[i] && ft_strncmp(mini->env[i], save, ft_strlen(save)))
		i++;
	fre = ft_strdup(mini->env[i] + ft_strlen(save));
	free(save);
	return (fre);
}

void	ft_setinput(t_lexer **red, t_proc *child, int *flag)
{
	while ((*red))
	{
		if ((*red)->token == LESS_LESS)
		{
			ft_take_input_from_terminal((*red)->next->str, child, *flag);
			(*flag) = 1;
		}
		else if ((*red)->token == LESS)
		{
			ft_take_input_from_file((*red)->next->str, child, *flag);
			(*flag) = 1;
		}
		(*red) = (*red)->prev;
	}
}

void	ft_setoutput(t_lexer **red, t_global *mini, int *flag, int *outfd)
{
	int	buffd;

	while (*red)
	{
		if ((*red)->token == GREAT_GREAT)
		{
			buffd = ft_greatgreat(mini, (*red)->next->str);
			if (*flag == 0)
			{
				close(*outfd);
				*outfd = buffd;
				(*flag) = 1;
			}
			else
				close(buffd);
		}
		else if ((*red)->token == GREAT)
		{
			buffd = ft_greatgreat(mini, (*red)->next->str);
			if (*flag == 0)
			{
				close(*outfd);
				*outfd = buffd;
				(*flag) = 1;
			}
			else
				close (buffd);
		}
		(*red) = (*red)->prev;
	}
}

char	*ft_set_path(t_global *mini, char **str)
{
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	path = ft_findinenv(mini, "PATH");
	paths = ft_split(path, ":");
	free(path);
	if (!paths)
		write(2, "PATH is empty.", 15);
	while (paths[i])
	{
		path = ft_path_arrange(paths[i], (*str));
		if (!access(path, F_OK))
		{
			free(*str);
			ft_freearr(&paths);
			return (path);
		}
		free(path);
		i++;
	}
	free(*str);
	ft_freearr(&paths);
	return (ft_strdup("Path doesn't exist"));
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
