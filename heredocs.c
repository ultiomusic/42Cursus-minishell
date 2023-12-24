/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:50:08 by baer              #+#    #+#             */
/*   Updated: 2023/12/23 17:48:22 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_heredocs(t_simple_cmds *temp)
{
	t_lexer	*test;
	int		i;

	i = 0;
	test = temp->redirections;
	while (test)
	{
		if (test->token == LESS_LESS)
		{
			i = test->i;
			ft_delete_lexer_node(i, temp);
			ft_delete_lexer_node(i, temp);
			test = ft_find_index(i, &(temp->redirections));
			continue ;
		}
		test = test->next;
	}
}
