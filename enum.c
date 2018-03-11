/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:19:54 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/11 23:11:23 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
// #include "hprintf.h"

// unsigned long	hash(char *str)
// {
// 	unsigned long	code;

// 	code = 0;
// 	while (*str)
// 	{
// 		code = *str + (code << 4) + (code << 7) - code;
// 		str++;
// 	}
// 	return (code & 524287);
// }

unsigned int	hash(char *str)
{
	unsigned long	code;

	code = 0;
	while (*str)
	{
		code = *str + (code << 6) + (code << 10) - code;
		str++;
	}
	return (code & 524287);
}

void mal(char **s)
{
	
	char *str;
	int i = 0;

	str = (char*)malloc(sizeof(char) * 10);
	str[9] = '\0';
	// printf("str0=%s\n", str);
	while (i < 10)
	{
		*str = i + 48;
		printf("hash=%u\n", hash("str"));
		i++;
		str++;

	}
	*s = str;
}

int		main(int ac, char **av)
{
	// char *s = "room114";
	// unsigned int code = hash(s);
	// printf("room1=%s\n", s);
	// printf("code=%u\n", code);

	// s = "room214";
	// code = hash(s);
	// printf("room2=%s\n", s);
	// printf("code=%u\n", code);

	char *ss;

	ss = NULL;

	mal(&ss);
	// printf("%s\n", ss);
	return (0);
}
