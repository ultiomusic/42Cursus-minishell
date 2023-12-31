/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 11:17:41 by ohayek            #+#    #+#             */
/*   Updated: 2024/01/02 21:59:51 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quicklyinitialize(int *i, int *flag, int *j)
{
	*i = -1;
	*flag = 0;
	*j = 0;
}

char	*ft_pathof(char *str, char **ev, t_global *mini)
{
	char	*path;
	int		i;

	(void)ev;
	i = 0;
	path = ft_strjoin(str, "=");
	while (mini->env[i])
	{
		if (!ft_strncmp(mini->env[i], path, ft_strlen(path)))
		{
			free(path);
			return (ft_strdup(mini->env[i]));
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
