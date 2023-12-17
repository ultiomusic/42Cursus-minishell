/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 04:35:54 by baer              #+#    #+#             */
/*   Updated: 2023/12/17 20:30:01 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_parser(t_global *mini)
{
	t_lexer	*lexer;
	t_lexer	*forward;

	lexer = mini->head;
	forward = lexer;
	mini->p_head = NULL;
	if (!lexer)
		return ;
	while (lexer)
	{
		while (forward && forward->token != PIPE)
			forward = forward->next;
		if (forward)
			forward = forward->next;
		ft_parser_pushback(mini, lexer);
		lexer = forward;
	}
	ft_init_matrix(mini);
	ft_init_builtin(mini);
	ft_parser_arrange(mini);
}

int	ft_pipesize(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer && lexer->token != PIPE)
	{
		i++;
		lexer = lexer->next;
	}
	return (i);
}

void	ft_init_matrix(t_global *mini)
{
	t_lexer			*temp;
	t_simple_cmds	*temp_s;
	int				i;

	temp = mini->head;
	temp_s = mini->p_head;
	while (temp_s)
	{
		i = 0;
		temp_s->str = malloc((ft_pipesize(temp) + 1) * sizeof(char *));
		while (temp && temp->token != PIPE)
		{
			temp_s->str[i++] = ft_strdup(temp->str);
			temp = temp->next; 
		}
		if (temp)
			temp = temp->next;
		temp_s->str[i] = NULL;
		temp_s = temp_s->next;
	}
}

void ft_parser_arrange(t_global *mini)
{
	t_lexer *red;
	t_lexer *temp;
	t_lexer **arr;
	t_lexer *save;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	temp = mini->p_head->redirections;
	arr = (t_lexer **)malloc(sizeof(t_lexer *) * (ft_lexersize(temp) + 1));
	arr[ft_lexersize(temp)] = NULL;
	save = mini->p_head->redirections;
	while(temp)
	{
		while(temp && (temp->token != LESS_LESS && temp->token != LESS))
			temp = temp->next;
		if(temp &&  (temp->token == LESS_LESS || temp->token == LESS))
		{	
			arr[i++] = temp;
			arr[i++] = temp->next;
			temp = temp->next;
		}
	}
	temp = save;
	while(temp)
	{
		while(temp && (temp->token != GREAT_GREAT && temp->token != GREAT))
			temp = temp->next;
		if(temp &&  (temp->token == GREAT_GREAT || temp->token == GREAT))
		{	
			arr[i++] = temp;
			arr[i++] = temp->next;
			temp = temp->next;
		}
	}
	red = arr[j++];
	save = red;
	while(arr[j] != NULL)
	{
		save->next = arr[j];
		save = save->next;
		j++;
	}
	mini->p_head->redirections = red;
	free(arr);
}