/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:35:25 by beeligul          #+#    #+#             */
/*   Updated: 2023/12/23 21:02:20 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] && i <= n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i <= n)
	{
		dest[i++] = '\0';
	}
	return (dest);
}

int	is_delimiter(char c, char *del)
{
	while (*del)
	{
		if (c == *del)
			return (1);
		del++;
	}
	return (0);
}

void	ft_spik6(char **str, int *is_token, int *count)
{
	if ((*is_token))
	{
		(*is_token) = 0;
		(*count)++;
	}
	(*count)++;
	(*str) += 2;
}

void	ft_spik7(char **str, int *is_token, int *count)
{
	if (*is_token)
	{
		*is_token = 0;
		(*count)++;
	}
	(*count)++;
	(*str)++;
}

int	count_tokens(char *str, char *del)
{
	int	count;
	int	is_token;

	count = 0;
	is_token = 0;
	while (*str)
	{
		if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0)
			ft_spik6(&str, &is_token, &count);
		else if (is_delimiter(*str, del))
			ft_spik7(&str, &is_token, &count);
		else
		{
			is_token = 1;
			str++;
		}
	}
	if (is_token)
		count++;
	return (count);
}
