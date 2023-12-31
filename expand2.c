/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:22:56 by ohayek            #+#    #+#             */
/*   Updated: 2024/01/02 21:33:43 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_qmark(char **exp, int *j, t_global *mini)
{
	char	*save;

	save = ft_itoa(mini->error);
	ft_stradd(exp, save, *j);
	*j += ft_strlen(save);
	free(save);
	return (1);
}
