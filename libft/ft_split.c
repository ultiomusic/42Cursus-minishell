/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:56:48 by beeligul          #+#    #+#             */
/*   Updated: 2024/01/02 18:56:48 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	int		i;

	if (ptr == NULL)
		return (malloc(size));
	if (!size)
		return (ptr);
	new_ptr = malloc(size);
	ft_memcpy(new_ptr, ptr, size);
	i = 0;
	free(ptr);
	return (new_ptr);
}

int	is_space_or_tab(char c)
{
	return (c == ' ' || c == '\t');
}

void	quote_func(const char **s, char *c)
{
	int	in_quote;

	in_quote = 0;
	while (**s)
	{
		if (**s == '"' || **s == '\'')
		{
			if (!in_quote)
				in_quote = **s;
			else if (in_quote == **s)
				in_quote = 0;
		}
		else if (in_quote)
			;
		else if (is_space_or_tab(**s) || ft_strchr(c, **s))
			break ;
		(*s)++;
	}
}

void	put_argument(char ***arr, int *arr_size, int length, const char *start)
{
	if (length > 0)
	{
		*arr = ft_realloc(*arr, (*arr_size + 1) * sizeof(char *));
		(*arr)[*arr_size] = malloc(length + 1);
		ft_strncpy((*arr)[*arr_size], start, length);
		(*arr)[*arr_size][length] = '\0';
		*arr_size += 1;
	}
}

char	**ft_split(const char *s, char *c)
{
	char		**arr;
	int			arr_size;
	int			length;
	const char	*start;

	arr = NULL;
	arr_size = 0;
	while (*s)
	{
		while (is_space_or_tab(*s) && *s)
			s++;
		if (*s == '\0')
			break ;
		start = s;
		quote_func(&s, c);
		length = s - start;
		put_argument(&arr, &arr_size, length, start);
		while (*s && (is_space_or_tab(*s) || ft_strchr(c, *s)))
			s++;
	}
	arr = ft_realloc(arr, (arr_size + 1) * sizeof(char *));
	arr[arr_size] = NULL;
	return (arr);
}
