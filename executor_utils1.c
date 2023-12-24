/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:39:27 by beeligul          #+#    #+#             */
/*   Updated: 2023/12/22 15:39:50 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_take_input_from_file(char *str, t_proc *child, int flag)
{
	int		fdfiledoc;
	int		fdheredoc;
	int		check;
	char	buffer;

	fdfiledoc = open(str, O_CREAT | O_RDWR, 0777);
	if (fdfiledoc < 0)
		write(2, "File couldn't be opened.", 25);
	fdheredoc = (*child).fd[1];
	while (read(fdfiledoc, &buffer, 1) > 0)
	{
		if (!flag)
			write(fdheredoc, &buffer, 1);
	}
	close(fdfiledoc);
}

int	ft_great(t_global *mini, char *str)
{
	int		ac;
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
	ac = access(path, F_OK);
	if (!ac)
		unlink(path);
	fd = open(str, O_RDWR | O_CREAT, 0777);
	if (fd < 0)
	{
		write(2, "Couldn't open the file.\n", 25);
		return (1);
	}
	return (fd);
}

int	ft_greatgreat(t_global *mini, char *str)
{
	int		fd;
	char	buffer;
	int		check;

	buffer = 1;
	check = 1;
	fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
	{
		write(2, "Couldn't open the file.\n", 25);
		return (1);
	}
	return (fd);
}
