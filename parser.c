/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:05:12 by baer              #+#    #+#             */
/*   Updated: 2023/12/23 17:49:16 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parser_firstnode(t_global *mini, t_lexer *lexer)
{
	t_simple_cmds	*new;
	t_lexer			*save;
	int				i;

	ft_skipinit(&new, 0);
	new->prev = NULL;
	save = lexer;
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token)
		{
			ft_parser_lexpush_back(new, lexer->str);
			ft_parser_lexpush_back(new, lexer->next->str);
			i = lexer->i;
			lexer = lexer->next->next;
			ft_delete_node(i, mini);
			ft_delete_node(i, mini);
			new->num_redirections++;
			continue ;
		}
		lexer = lexer->next;
	}
	mini->p_head = new;
}

void	ft_skipinit(t_simple_cmds **new, int flag)
{
	static int	i = 0;

	if (flag)
	{
		i = 0;
		return ;
	}
	(*new) = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
	(*new)->next = NULL;
	(*new)->num_redirections = 0;
	(*new)->str = NULL;
	(*new)->redirections = NULL;
}

void	ft_parser_lastnode(t_global *mini, t_lexer *lexer)
{
	t_simple_cmds	*new;
	t_simple_cmds	*temp;
	int				i;

	ft_skipinit(&new, 0);
	temp = mini->p_head;
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token)
		{
			ft_parser_lexpush_back(new, lexer->str);
			ft_parser_lexpush_back(new, lexer->next->str);
			i = lexer->i;
			lexer = lexer->next->next;
			ft_delete_node(i, mini);
			ft_delete_node(i, mini);
			new->num_redirections++;
			continue ;
		}
		lexer = lexer->next;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

void	ft_parser_pushback(t_global *mini, t_lexer *lexer)
{
	if (!mini->p_head)
		ft_parser_firstnode(mini, lexer);
	else
		ft_parser_lastnode(mini, lexer);
}
