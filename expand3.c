/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:34:30 by beeligul          #+#    #+#             */
/*   Updated: 2023/12/18 19:34:33 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quicklyinitialize(int *i, int *flag, int *j)
{
	*i = -1;
	*flag = 0;
	*j = 0;
}

char	*ft_pathof(char *str, char **ev)
{
	char	*path;
	int		i;

	i = 0;
	path = ft_strjoin(str, "=");
	while (ev[i])
	{
		if (!ft_strncmp(ev[i], path, ft_strlen(path)))
		{
			free(path);
			return (ev[i]);
		}
		i++;
	}
	free(path);
	return (ft_strdup(""));
}

int	ft_allvalid(char c)
{
	if (c == '_' || ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

void	ft_stradd(char **exp, char *str, int j)
{
	int	i;

	i = 0;
	while (str[i])
		(*exp)[j++] = str[i++];
	(*exp)[j] = '\0';
}
