/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:15:58 by baer              #+#    #+#             */
/*   Updated: 2023/12/23 19:47:09 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_single_commands(t_global *mini)
{
	t_proc			child;
	t_simple_cmds	*cmd;
	t_lexer			*red;
	t_lexer			*save;
	char			buffer;
	char			*buf;
	int				i;
	int				outfd;
	int				flag;

	i = 0;
	outfd = dup(STDOUT_FILENO);
	if (pipe(child.fd) == -1)
		write(2, "Pipe couldn't be opened.", 25);
	cmd = mini->p_head;
	if(cmd->str[0])
		cmd->str[0] = ft_set_path(mini, &(cmd->str[0]));
	flag = 0;
	red = cmd->redirections;
	while (red && red->next)
		red = red->next;
	save = red;
	child.pid = fork();
	if(child.pid == 0)
	{
		ft_setinput(&red, &child, &flag);
		red = save;
		flag = 0;
		ft_setoutput(&red, mini, &flag, &outfd);
	}
	if (child.pid == 0)
	{
		dup2(child.fd[0], STDIN_FILENO);
		dup2(outfd, STDOUT_FILENO);
		close(child.fd[1]);
		close(child.fd[0]);
		// BİLEN BİRİNE KAPATMALI MISIN KAPATMAMALI MISIN SOR
		if(execve(cmd->str[0], cmd->str, mini->env))
		{
			write(2,"Couldn't execute the command\n",30);
			exit(1);
		}
	}
	waitpid(child.pid, NULL, 0);
	close(child.fd[0]);
	close(child.fd[1]);
	close(outfd);
	return (0);
}
/*
void	close_file_descriptors(t_proc *child, int outfd)
{
	close(child->fd[0]);
	close(outfd);
}

void	setup_child_stdin_stdout(t_proc *child, int outfd)
{
	close(child->fd[1]);
	dup2(child->fd[0], STDIN_FILENO);
	dup2(outfd, STDOUT_FILENO);
	close(child->fd[0]);
}

void	execute_command(t_simple_cmds *cmd, t_global *mini)
{
	execve(cmd->str[0], cmd->str, mini->env);
}

int	ft_execute_single_commands(t_global *mini)
{
	t_proc			child;
	t_simple_cmds	*cmd;
	t_lexer			*red;
	int				outfd;

	cmd = mini->p_head;
	child = {0};
	red = cmd->redirections;
	outfd = dup(STDOUT_FILENO);
	if (pipe(child.fd) == -1)
		write(2, "Pipe couldn't be opened.", 25);
	cmd->str[0] = ft_set_path(mini, &(cmd->str[0]));
	while (red && red->next)
		red = red->next;
	cmd->flag = 0;
	ft_setinput(&red, &child, &(cmd->flag));
	ft_setoutput(&red, mini, &(cmd->flag), &outfd);
	child.pid = fork();
	if (child.pid == 0)
	{
		close_file_descriptors(&child, outfd);
		setup_child_stdin_stdout(&child, outfd);
		execute_command(cmd, mini);
	}
	waitpid(child.pid, NULL, 0);
	close_file_descriptors(&child, outfd);
	return (0);
}
*/

void	ft_take_input_from_terminal(char *str, t_proc *child, int flag)
{
	int		fdheredoc;
	char	*line;

	fdheredoc = (*child).fd[1];
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, str) == 0)
			break ;
		else if (!flag)
		{
			write(fdheredoc, line, ft_strlen(line));
			write(fdheredoc, "\n", 1);
		}
	}
	free(line);
}

/*
	parser redirectorysinde > lü komutlar küçüktürlü komutlardan sonra gelecek.
	her directory için komut ayrı çalışacak
	her komut için input file.
*/