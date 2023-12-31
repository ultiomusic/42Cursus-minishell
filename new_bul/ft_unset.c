/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:25:37 by baer              #+#    #+#             */
/*   Updated: 2024/01/02 19:01:16 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset_errors(t_global *mini, t_simple_cmds *parser)
{
	int	i;

	(void)mini;
	i = 0;
	while (parser->str[i])
	{
		if (parser->str[1][i++] == '/')
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(parser->str[1], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (EXIT_FAILURE);
		}
	}
	return (0);
}

char	**ft_setenvminus(char **ev, int j)
{
	int		i;
	int		k;
	int		c;
	char	**arr;

	i = 0;
	while (ev[i])
		i++;
	arr = malloc(sizeof(char *) * (--i + 1));
	arr[i] = NULL;
	k = 0;
	c = 0;
	while (k < i)
	{
		if (c != j)
			arr[k++] = ft_strdup(ev[c++]);
		else
			c++;
	}
	return (arr);
}

int	ft_toequal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

void	ft_delvar(t_global *mini, char *str, int j)
{
	char	**env;
	char	**ex;

	env = ft_setenv(mini->env);
	ex = ft_setenv(mini->export);
	while (env[++j])
	{
		if (!ft_strncmp(env[j], str, ft_toequal(env[j])))
		{
			free_tokens(mini->env);
			mini->env = ft_setenvminus(env, j);
		}
	}
	j = -1;
	while (ex[++j])
	{
		if (!ft_strncmp(ex[j], str, ft_toequal(ex[j])))
		{
			free_tokens(mini->export);
			mini->export = ft_setenvminus(ex, j);
		}
	}
	free_tokens(ex);
	free_tokens(env);
}

int	ft_unset(t_global *mini, t_simple_cmds *parser)
{
	int	i;

	i = 0;
	if (!parser->str[1])
		return (0);
	if (ft_unset_errors(mini, parser))
		return (1);
	while (parser->str[i])
		ft_delvar(mini, parser->str[i++], -1);
	return (0);
}
