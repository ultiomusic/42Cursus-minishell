/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:39:27 by beeligul          #+#    #+#             */
/*   Updated: 2023/12/25 19:00:34 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_take_input_from_file(char *str, t_proc *child, int flag)
{
	int		fdfiledoc;
	int		fdheredoc;
	char	buffer;
	if(!flag)
	{
	fdfiledoc = open(str, O_RDWR, 0777);
	if (fdfiledoc < 0)
	{
		write(2,"bash:",6);
		perror(str);
		g_global.error_num = 1;
	}
	fdheredoc = (*child).fd[1];
	while (read(fdfiledoc, &buffer, 1) > 0)
	{
		if (!flag)
			write(fdheredoc, &buffer, 1);
	}
	close(fdfiledoc);
	}
}

int	ft_great(t_global *mini, char *str)
{
	int		fd;
	char	*path;
	char	*save;

	path = ft_findinenv(mini, "PWD");
	save = path;
	path = ft_strjoin(path, "/");
	free(save);
	save = path;
	path = ft_strjoin(path, str);
	free(save);
	fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		write(2,"bash: ",7);
		perror(str);
		g_global.error_num = 1;
		return -1;
	}
	return (fd);
}

int	ft_greatgreat(t_global *mini, char *str)
{
	int		fd;
	char	buffer;
	int		check;

	buffer = 1;
	if(mini)
		check = 1;
	fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
	{
		write(2,"bash: ",7);
		perror(str);
		g_global.error_num = 1;
		return -1;
	}
	return (fd);
}
