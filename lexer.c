/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:33:54 by beeligul          #+#    #+#             */
/*   Updated: 2023/12/18 19:33:55 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_token(char *str)
{
	if (!ft_strcmp("|", str))
		return (1);
	if (!ft_strcmp(">>", str))
		return (3);
	if (!ft_strcmp(">", str))
		return (2);
	if (!ft_strcmp("<<", str))
		return (5);
	if (!ft_strcmp("<", str))
		return (4);
	return (0);
}

void	ft_first_node(t_global *mini, char *str)
{
	mini->head = (t_lexer *)malloc(sizeof(t_lexer));
	if (!mini->head)
		return ;
	mini->head->next = NULL;
	mini->head->prev = NULL;
	mini->head->token = ft_find_token(str);
	mini->head->str = ft_strdup(str);
	mini->head->i = 0;
	if (str[0] == '"')
		mini->head->is_quote = 2;
	else if (str[0] == '\'')
		mini->head->is_quote = 1;
	else
		mini->head->is_quote = 0;
}

void	ft_last_node(t_global *mini, char *str)
{
	t_lexer	*new;
	t_lexer	*temp;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return ;
	new->next = NULL;
	new->token = ft_find_token(str);
	new->str = ft_strdup(str);
	temp = mini->head;
	while (temp->next)
		temp = temp->next;
	new->prev = temp;
	temp->next = new;
	new->i = new->prev->i + 1;
	if (str[0] == '"')
		new->is_quote = 2;
	else if (str[0] == '\'')
		new->is_quote = 1;
	else
		new->is_quote = 0;
}

void	ft_push_back(t_global *mini, char *str)
{
	if (!mini->head)
	{
		ft_first_node(mini, str);
		return ;
	}
	ft_last_node(mini, str);
}

void	ft_init_lexer(t_global *mini, char *line)
{
	char	**lexers;
	char	**tokens;
	int		i;
	int		j;

	lexers = ft_split(line, "\t ");
	if (!lexers)
		return ;
	i = 0;
	while (lexers[i])
	{
		if (lexers[i][0] != '"' && lexers[i][0] != '\'')
			tokens = ft_split_tok(lexers[i], "|<>");
		else
			tokens = ft_split(lexers[i], " ");
		j = 0;
		while (tokens[j])
			ft_push_back(mini, tokens[j++]);
		free_tokens(tokens);
		i++;
	}
	free_tokens(lexers);
}
