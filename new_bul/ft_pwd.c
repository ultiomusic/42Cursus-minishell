/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:01:11 by beeligul          #+#    #+#             */
/*   Updated: 2024/01/02 21:39:51 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_printexport(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		printf("declare -x %s\n", str[i++]);
	return (0);
}

int	ft_pwd(t_global *mini, struct s_simple_cmds *head)
{
	char	cwd[1024];

	(void)head;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putchar_fd('\n', 1);
	}
	else
	{
		ft_putstr_fd("pwd: error getting current directory\n", 2);
		mini->error = 1;
	}
	(void)mini;
	return (0);
}
