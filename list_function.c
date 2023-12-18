/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:08:02 by baer              #+#    #+#             */
/*   Updated: 2023/12/18 19:38:32 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parsersize(t_simple_cmds *parser)
{
	int	i;

	i = 0;
	while (parser)
	{
		i++;
		parser = parser->next;
	}
	return (i);
}

int	ft_lexersize(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer)
	{
		i++;
		lexer = lexer->next;
	}
	return (i);
}

void	ft_delete_lexer_node(int index, t_simple_cmds *temp2)
{
	t_lexer	*temp;

	temp = temp2->redirections;
	if (!temp)
		return ;
	while (temp->i != index && temp->next)
		temp = temp->next;
	if (temp->i != index)
		return ;
	if (temp->prev)
		temp->prev->next = temp->next;
	else
		temp2->redirections = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	free(temp->str);
	free(temp);
	ft_set_lexer_index(temp2);
}

void	ft_set_lexer_index(t_simple_cmds *temp2)
{
	t_lexer	*temp;
	int		i;

	temp = temp2->redirections;
	i = 0;
	while (temp)
	{
		temp->i = i++;
		temp = temp->next;
	}
}
