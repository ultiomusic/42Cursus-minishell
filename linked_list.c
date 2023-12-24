/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:36:02 by beeligul          #+#    #+#             */
/*   Updated: 2023/12/19 18:29:33 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_index(t_global *mini)
{
	t_lexer	*temp;
	int		i;

	temp = mini->head;
	i = 0;
	while (temp)
	{
		temp->i = i++;
		temp = temp->next;
	}
}

t_lexer	*ft_find_index(int i, t_lexer **lexer)
{
	t_lexer	*temp;

	temp = (*lexer);
	while (temp)
	{
		if (temp->i == (*lexer)->i)
			return (temp);
		temp = temp->next;
	}
	write(2, "\nindex problem\n", 16);
	return (NULL);
}

void	ft_delete_node(int index, t_global *mini)
{
	t_lexer	*temp;

	temp = mini->head;
	if (!temp)
		return ;
	while (temp->i != index && temp->next)
		temp = temp->next;
	if (temp->i != index)
		return ;
	if (temp->prev)
		temp->prev->next = temp->next;
	else
		mini->head = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	free(temp->str);
	free(temp);
	ft_set_index(mini);
}

int	ft_size_cmds(t_global *mini)
{
	t_simple_cmds	*temp;
	int				size;

	size = 0;
	temp = mini->p_head;
	while (temp)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}
