/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:42:45 by baer              #+#    #+#             */
/*   Updated: 2024/01/02 21:58:31 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setmultiinput(t_lexer *red, t_proc *childs, int *flag, int i)
{
	t_lexer	*save;
	t_lexer	*save2;
	int		fflag;

	save2 = firstskip(red, &save, &fflag);
	while (save2)
	{
		if (save2->token == LESS_LESS)
		{
			ft_ifskip1(&save, &save2, &fflag, flag);
			ft_take_multiinput_from_terminal(save2->next->str, childs,
				fflag, i);
			(fflag) = 1;
		}
		else if (save2->token == LESS)
		{
			ft_ifskip1(&save, &save2, &fflag, flag);
			ft_take_multiinput_from_file(save2->next->str, childs, fflag, i);
			(fflag) = 1;
		}
		save2 = save2->next;
	}
}

void	ft_ifskip1(t_lexer **save, t_lexer **save2, int *fflag, int *flag)
{
	if ((*save2) == (*save))
	{
		(*fflag) = 0;
		(*flag) = 1;
	}
}

t_lexer	*firstskip(t_lexer *red, t_lexer **save, int *fflag)
{
	t_lexer	*save2;

	*save = NULL;
	save2 = (red);
	*(fflag) = 1;
	while (save2 && save2->prev)
		save2 = save2->prev;
	while ((red))
	{
		if ((red)->token == LESS_LESS)
		{
			(*save) = (red);
			break ;
		}
		else if ((red)->token == LESS)
		{
			(*save) = (red);
			break ;
		}
		(red) = (red)->prev;
	}
	return (save2);
}

void	ft_take_multiinput_from_terminal(char *str, t_proc *child,
			int flag, int i)
{
	int		fdheredoc;
	char	*line;

	if (!fork())
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
			if (line)
				free(line);
		}
		ft_smoothoperator(child);
	}
	else
		wait(NULL);
}

void	ft_smoothoperator(t_proc *child)
{
	int	j;

	j = 0;
	while (j <= child[0].parsersize)
	{
		close(child[j].fd[1]);
		close(child[j].fd[0]);
		j++;
	}
	exit(0);
}
