/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:00:28 by beeligul          #+#    #+#             */
/*   Updated: 2024/01/02 21:39:46 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_set_export_according_to_env(t_global *mini)
{
	int	size;
	int	i;

	size = 0;
	while (mini->env[size])
		size++;
	free_tokens(mini->export);
	mini->export = (char **)malloc(sizeof(char *) * size + 1);
	i = 0;
	while (mini->env[i])
	{
		mini->export[i] = ft_strdup(mini->env[i]);
		i++;
	}
	mini->export[i] = NULL;
}

void	ft_delete_oldpwd(t_global *mini)
{
	char	**env;
	int		i;
	int		j;

	env = ft_setenv(mini->env);
	free_tokens(mini->env);
	i = 0;
	while (env[i])
		i++;
	mini->env = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7))
			mini->env[j++] = ft_strdup(env[i]);
		i++;
	}
	mini->env[j] = NULL;
	free_tokens(env);
}

void	directions(t_global *mini, t_simple_cmds *parser, int *ret)
{
	if (!parser->str[1] || !parser->str[1][0])
		*ret = ft_setdir(mini, "HOME=");
	else if (!ft_strcmp(parser->str[1], "-"))
		*ret = ft_setdir(mini, "OLDPWD=");
	else if (!ft_strcmp(parser->str[1], "~"))
		*ret = ft_setdir(mini, "HOME=");
	else
	{
		*ret = chdir(parser->str[1]);
		if (*ret)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(parser->str[1], 2);
			perror(" ");
		}
	}
}

int	ft_cdskip(t_global *mini, t_simple_cmds *parser, int ret)
{
	directions(mini, parser, &ret);
	if (ret)
	{
		mini->error = 1;
		return (1);
	}
	if (no_pwd(mini->env))
	{
		ft_delete_oldpwd(mini);
		return (0);
	}
	ft_set_pwd(mini, parser->str[1]);
	ft_set_export_according_to_env(mini);
	return (0);
}

int	ft_cd(t_global *mini, t_simple_cmds *parser)
{
	int	ret;

	ret = 0;
	return (ft_cdskip(mini, parser, ret));
}
