/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:57:17 by beeligul          #+#    #+#             */
/*   Updated: 2024/01/02 18:57:17 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	r = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (r == NULL)
		return (NULL);
	i = 0;
	while (*s1 != '\0')
		r[i++] = *s1++;
	while (*s2 != '\0')
		r[i++] = *s2++;
	r[i] = '\0';
	return (r);
}
