/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 19:08:30 by oantonen          #+#    #+#             */
/*   Updated: 2017/12/24 17:02:40 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *ptr;

	ptr = dst;
	while (len)
	{
		if (!*src)
			break ;
		else
			*ptr++ = *src++;
		len--;
	}
	while (len)
	{
		*ptr++ = '\0';
		len--;
	}
	return (dst);
}
