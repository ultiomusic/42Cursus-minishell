/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:22:56 by ohayek            #+#    #+#             */
/*   Updated: 2023/12/25 15:38:58 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_qmark(char **exp, int *j)
{
	char	*save;

	save = ft_itoa(g_global.error_num);
	ft_stradd(exp, save, *j);
	*j += ft_strlen(save);
	free(save);
	return (1);
}
