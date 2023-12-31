/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:55:24 by baer              #+#    #+#             */
/*   Updated: 2024/01/02 19:08:08 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printmatrix(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != NULL)
	{
		while (str[i][j] != '\0')
			write(1, str[i] + j++, 1);
		write(1, " ", 1);
		j = 0;
		i++;
	}
	write(1, "\n", 1);
}

void	ft_executer(t_global *mini)
{
	if (ft_parsersize(mini->p_head) == 1)
		ft_execute_single_commands(mini);
	else if (ft_parsersize(mini->p_head) >= 1)
		ft_execute_multiple_commands(mini);
}
