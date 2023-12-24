/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:35:10 by beeligul          #+#    #+#             */
/*   Updated: 2023/12/19 18:34:19 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_spik(char ***tokens, int *index, int *token_length, char **str)
{
	if (*token_length > 0)
	{
		(*tokens)[*index] = (char *)malloc((*token_length + 1) \
			* sizeof(char));
		ft_strncpy((*tokens)[*index], (*str) - *token_length, *token_length);
		(*tokens)[*index][*token_length] = '\0';
		(*index)++;
	}
	(*tokens)[*index] = (char *)malloc(3 * sizeof(char));
	ft_strncpy((*tokens)[*index], (*str), 2);
	(*tokens)[*index][2] = '\0';
	(*index)++;
	(*str) += 2;
	(*token_length) = 0;
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (tokens)
	{
		while (tokens[i] != NULL)
			free(tokens[i++]);
		free(tokens);
	}
}

char	**ft_setenv(char **ev)
{
	int		i;
	char	**arr;

	i = 0;
	while (ev[i])
		i++;
	arr = malloc(sizeof(char *) * (i + 1));
	arr[i] = NULL;
	while (i--)
		arr[i] = ft_strdup(ev[i]);
	return (arr);
}
