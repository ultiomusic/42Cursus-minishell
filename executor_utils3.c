/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:10:29 by beeligul          #+#    #+#             */
/*   Updated: 2023/12/30 21:22:02 by baer             ###   ########.fr       */
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
	if(mini->env[i] == NULL)
	return NULL;
	fre = ft_strdup(mini->env[i] + ft_strlen(save));
	free(save);
	return (fre);
}

void	ft_setinput(t_lexer **red, t_proc *child, int *flag)
{
	t_lexer *save;
	t_lexer *save2;

	if(!(*red))
		return ;
	save = NULL;
	save2 = (*red);
	while(save2->prev)
		save2 = save2->prev;
	while ((*red))
	{
		if ((*red)->token == LESS_LESS)
		{
			save = (*red);
			break;
		}
		else if ((*red)->token == LESS)
		{
			save = (*red);
			break;
		}
		(*red) = (*red)->prev;
	}
	(*flag) = 1;
	while(save2)
	{
		if (save2->token == LESS_LESS)
		{
			if(save2 == save)
			(*flag) = 0;
			ft_take_input_from_terminal(save2->next->str, child, *flag);
			(*flag) = 1;
		}
		else if (save2->token == LESS)
		{
			if(save2 == save)
			(*flag) = 0;
			ft_take_input_from_file(save2->next->str, child, *flag);
			(*flag) = 1;
		}
		save2 = save2->next;
	}
}

//ft_take_input_from_terminal((*red)->next->str, child, *flag);
//ft_take_input_from_file((*red)->next->str, child, *flag);

void	ft_setoutput(t_lexer **red, t_global *mini, int *flag, int *outfd)
{
	int buffd;
	
	while (*red)
	{
		if ((*red)->token == GREAT_GREAT)
		{
			buffd = ft_greatgreat(mini, (*red)->next->str);
			if(*flag == 0)
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
			buffd = ft_great(mini, (*red)->next->str);
			if(*flag == 0)
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
	if(path == NULL)
		return (*str);
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