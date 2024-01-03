/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:55:42 by beeligul          #+#    #+#             */
/*   Updated: 2024/01/02 18:55:42 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content)
{
	t_list	*r;

	r = (t_list *)malloc(sizeof(t_list));
	if (!r)
		return (NULL);
	r->content = (void *)content;
	r->next = NULL;
	return (r);
	return (NULL);
}
