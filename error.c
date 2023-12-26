/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:35:03 by beeligul          #+#    #+#             */
/*   Updated: 2023/12/25 14:49:44 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_tokens(t_global *mini)
{
	t_lexer	*tmp;

	tmp = mini->head;
	while (tmp)
	{
		if (tmp->token >= 2 && tmp->next && tmp->next->token)
		{
			ft_putstr_fd("Token Error\n", 2);
			g_global.error_num = 258;
			return (0);
		}
		else if (tmp->token >= 2 && !tmp->next)
		{
			ft_putstr_fd("Token Error\n", 2);
			g_global.error_num = 258;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	ft_check_pipe(t_global *mini)
{
	t_lexer	*tmp;

	tmp = mini->head;
	while (tmp)
	{
		if (tmp->token == 1 && tmp->prev && tmp->prev->token == 1)
		{
			ft_putstr_fd("pipe Error\n", 2);
			g_global.error_num = 258;
			return (0);
		}
		else if (tmp->token == 1 && (!tmp->next || !tmp->prev))
		{
			ft_putstr_fd("pipe Error\n", 2);
			g_global.error_num = 258;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	ft_check_error(t_global *mini)
{
	return (!ft_check_pipe(mini) || !ft_check_tokens(mini));
}
