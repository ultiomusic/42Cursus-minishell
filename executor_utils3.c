/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:10:29 by beeligul          #+#    #+#             */
/*   Updated: 2024/01/04 16:37:20 by baer             ###   ########.fr       */
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
	if (mini->env[i] == NULL)
		return ("Yok");
	fre = ft_strdup(mini->env[i] + ft_strlen(save));
	free(save);
	return (fre);
}

void	ft_setinput(t_lexer **red, t_proc *child, int *flag, t_global *mini)
{
	t_lexer	*save;
	t_lexer	*save2;

	if (!(*red))
		return ;
	save2 = smoothskip(red, &save, flag);
	while (save2)
	{
		if (save2->token == LESS_LESS)
		{
			if (save2 == save)
				(*flag) = 0;
			ft_take_input_from_terminal(save2->next->str, child, *flag);
			(*flag) = 1;
		}
		else if (save2->token == LESS)
		{
			if (save2 == save)
				(*flag) = 0;
			ft_take_input_from_file(mini, save2->next->str, child, *flag);
			(*flag) = 1;
		}
		save2 = save2->next;
	}
}

t_lexer	*smoothskip(t_lexer **red, t_lexer **save, int *flag)
{
	t_lexer	*save2;

	(*save) = NULL;
	save2 = (*red);
	while (save2->prev)
		save2 = save2->prev;
	while ((*red))
	{
		if ((*red)->token == LESS_LESS)
		{
			(*save) = (*red);
			break ;
		}
		else if ((*red)->token == LESS)
		{
			(*save) = (*red);
			break ;
		}
		(*red) = (*red)->prev;
	}
	(*flag) = 1;
	return (save2);
}

void	ft_setoutput(t_lexer **red, t_global *mini, int *flag, int *outfd)
{
	int	buffd;

	while (*red)
	{
		if ((*red)->token == GREAT_GREAT)
		{
			buffd = ft_greatgreat(mini, (*red)->next->str);
			ft_smoooooth(&buffd, outfd, flag);
		}
		else if ((*red)->token == GREAT)
		{
			buffd = ft_great(mini, (*red)->next->str);
			ft_smoooooth(&buffd, outfd, flag);
		}
		(*red) = (*red)->prev;
	}
}

void	ft_smoooooth(int *buffd, int *outfd, int *flag)
{
	if (*flag == 0)
	{
		close(*outfd);
		*outfd = *buffd;
		(*flag) = 1;
	}
	else
		close(*buffd);
}
