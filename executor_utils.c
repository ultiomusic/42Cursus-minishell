/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:15:58 by baer              #+#    #+#             */
/*   Updated: 2023/12/18 19:50:56 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_single_commands(t_global *mini)
{
	t_simple_cmds	*temp;
	t_proc			process;
	int				fdheredoc;
	char			*comm;
	int				save;
	int				status;

	temp = mini->p_head;
	comm = temp->str[0];
	temp->str[0] = ft_strjoin("/bin/", temp->str[0]);
	if (temp->in_her >= 1)
	{
		fdheredoc = open(temp->hd_file_name, O_CREAT | O_RDWR, 777);
		ft_set_heredocs(temp);
		ft_clear_heredocs(temp);
	}
	process.pid = fork();
	if (process.pid == 0)
	{
		if (temp->in_her)
			dup2(fdheredoc, STDIN_FILENO);
		save = execve(temp->str[0], temp->str, mini->env);
	}
	waitpid(process.pid, &status, 0);
	free(comm);
	if (temp->in_her)
	{
		close(fdheredoc);
		unlink(temp->hd_file_name);
	}
	return (0);
}

/*
	parser redirectorysinde > lü komutlar küçüktürlü komutlardan sonra gelecek.
	her directory için komut ayrı çalışacak
	her komut için input file.
*/