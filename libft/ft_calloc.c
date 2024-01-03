/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:54:29 by beeligul          #+#    #+#             */
/*   Updated: 2024/01/02 18:54:30 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;
	size_t	temp;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	temp = nmemb * size;
	if (temp / size != nmemb)
		return (NULL);
	s = malloc(temp);
	if (!s)
		return (NULL);
	ft_bzero(s, temp);
	return (s);
}
