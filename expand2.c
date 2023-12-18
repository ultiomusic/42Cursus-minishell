/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:34:36 by beeligul          #+#    #+#             */
/*   Updated: 2023/12/18 19:34:38 by beeligul         ###   ########.fr       */
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
