/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleutils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:12:24 by beeligul          #+#    #+#             */
/*   Updated: 2024/01/02 21:39:39 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_errorarranger(t_global *mini, int out)
{
	(void)mini;
	g_global.sig = 0;
	if (WIFEXITED(out))
		mini->error = WEXITSTATUS(out);
	else if (WIFSIGNALED(out))
		mini->error = WTERMSIG(out) + 128;
}
