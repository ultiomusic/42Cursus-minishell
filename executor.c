/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:55:24 by baer              #+#    #+#             */
/*   Updated: 2023/12/17 20:31:49 by baer             ###   ########.fr       */
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
	t_lexer	*lexer;

	lexer = mini->p_head->redirections;
	while (lexer)
	{
		printf("%s ", lexer->str);
		lexer = lexer->next;
	}
}

/*void	ft_executer(t_global *mini)
{
	t_lexer *temp;
	ft_clear_heredocs(mini->p_head);
	temp = mini->p_head->redirections;
	while(temp)
	{
		printf("sring:%s\n",temp->str);
		temp = temp->next;
	}
}*/

/*int	parsersize;
	int ret;
	t_simple_cmds *temp;
	
	temp = mini->p_head;
	parsersize = ft_parsersize(temp);
	if(parsersize == 1)
		ret = ft_execute_single_commands(mini);
	else
		write(2,"cok komut war",14);*/

/*
	bir input file oluştur inputları at içine sonra redirectionsları 
	teker teker çalıştır.
*/