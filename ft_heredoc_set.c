/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:50:08 by baer              #+#    #+#             */
/*   Updated: 2023/12/17 19:07:41 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_set_heredocs(t_simple_cmds *temp)
{
	int	fdheredoc;
	char *line;
	t_lexer *lextemp;
	
	lextemp = temp->redirections;
	fdheredoc = open(temp->hd_file_name,O_CREAT | O_RDWR , 0777);
	while(lextemp)
	{
	while(lextemp && lextemp->token != LESS_LESS)
		lextemp = lextemp->next;
	while(lextemp)
	{
		line = readline("> ");
		if (ft_strcmp(line, lextemp->next->str) == 0)
			break;
		else
		{
			write(fdheredoc,line,ft_strlen(line));
			write(fdheredoc,"\n",1);
		}
	}
	if(lextemp)
		lextemp = lextemp->next;
	}
	free(line);
	close(fdheredoc);
}

void ft_clear_heredocs(t_simple_cmds *temp)
{
	t_lexer *test;
	int		i;

	i = 0;
	test = temp->redirections;
	while(test)
	{	
		if(test->token == LESS_LESS)
		{
			i = test->i;
			ft_delete_lexer_node(i,temp);
			ft_delete_lexer_node(i,temp);
			test = ft_find_index(i,&(temp->redirections));
			continue;
		}
		test = test->next;
	}
}