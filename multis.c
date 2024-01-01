/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:42:45 by baer              #+#    #+#             */
/*   Updated: 2023/12/30 19:38:04 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setmultiinput(t_lexer *red, t_proc *childs, int *flag, int i)
{
	t_lexer *save;
	t_lexer *save2;
	int		fflag;

	save = NULL;
	save2 = (red);
	while(save2 && save2->prev)
		save2 = save2->prev;
	while ((red))
	{
		if ((red)->token == LESS_LESS)
		{
			save = (red);
			break;
		}
		else if ((red)->token == LESS)
		{
			save = (red);
			break;
		}
		(red) = (red)->prev;
	}
	(fflag) = 1;
	while(save2)
	{
		if (save2->token == LESS_LESS)
		{
			if(save2 == save)
			{
				(fflag) = 0;
				(*flag) = 1;
			}
			ft_take_multiinput_from_terminal(save2->next->str, childs, fflag, i);
			(fflag) = 1;
		}
		else if (save2->token == LESS)
		{
			if(save2 == save)
			{
				(fflag) = 0;
				(*flag) = 1;
			}
			ft_take_multiinput_from_file(save2->next->str, childs, fflag, i);
			(fflag) = 1;
		}
		save2 = save2->next;
	}
}

void	ft_take_multiinput_from_terminal(char *str, t_proc *child, int flag, int i)
{
	int		fdheredoc;
	char	*line;
	int		pid;
	int		j;

	j = 0;
	pid = fork();
	if(pid == 0)
	{
		fdheredoc = child[i].fd[1];
		while (1)
		{
			line = readline("> ");
			if (ft_strcmp(line, str) == 0 || !line)
				break ;
			else if (!flag)
			{
				write(fdheredoc, line, ft_strlen(line));
				write(fdheredoc, "\n", 1);
			}
			if(line)
				free(line);
			}
		while(j <= child[0].parsersize)
		{
		close(child[j].fd[1]);
		close(child[j].fd[0]);
		j++;
		}
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

void	ft_take_multiinput_from_file(char *str, t_proc *child, int flag, int i)
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
	fdheredoc = child[i].fd[1];
	while (read(fdfiledoc, &buffer, 1) > 0)
	{
		if (!flag)
			write(fdheredoc, &buffer, 1);
	}
	close(fdfiledoc);
	}
}