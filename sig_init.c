/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 21:56:19 by beeligul          #+#    #+#             */
/*   Updated: 2024/01/02 21:57:25 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_init(void)
{
	suppress_output();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
