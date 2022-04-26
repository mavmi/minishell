/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:50:51 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/03 15:50:52 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	counter;

	if (dst == src)
		return (dst);
	counter = 0;
	while (counter < n)
	{
		*(unsigned char *)(dst + counter) = *(unsigned char *)(src + counter);
		counter++;
	}
	return (dst);
}
