/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 21:19:45 by oantonen          #+#    #+#             */
/*   Updated: 2018/02/17 19:20:53 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_push_back(t_list **begin_list, t_list *new)
{
	t_list	*ptr;

	ptr = NULL;
	if (begin_list)
	{
		ptr = *begin_list;
		while (ptr != NULL)
			ptr = ptr->next;
		ptr = new;
	}
}
