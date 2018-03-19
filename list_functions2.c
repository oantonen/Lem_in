/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 22:27:31 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/19 22:01:42 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

void	li_lst_insert(t_list *first, t_list *second, t_list *new)
{
	first->next = new;
	new->next = second;
}

void	li_sort_list(t_list **new, t_list *ptr, int size)
{
	t_list *ptr2;
	t_list *ptr3;

	ptr2 = *new;
	while (ptr2)
	{
		ptr3 = ptr2->next;
		if (ptr->content_size < ptr2->content_size)
		{
			ft_lstadd(new, ft_lstnew(((t_data*)ptr->content), size));
			break ;
		}
		else if (ptr3 != NULL && size <= ptr3->content_size)
		{
			ptr3 = ft_lstnew(((t_data*)ptr->content), size);
			li_lst_insert(ptr2, ptr2->next, ptr3);
			break ;
		}
		else if (ptr2->next == NULL)
		{
			ptr2->next = ft_lstnew(((t_data*)ptr->content), size);
			break ;
		}
		ptr2 = ptr2->next;
	}
}

void	sort_end_links(t_list **end)
{
	t_list *ptr;
	t_list *new;

	ptr = *end;
	new = NULL;
	if (ptr->content_size != 0)
		ft_lstadd(&new, ft_lstnew(((t_data*)ptr->content), ptr->content_size));
	ptr = ptr->next;
	while (ptr)
	{
		if (ptr->content_size != 0)
			li_sort_list(&new, ptr, ptr->content_size);
		ptr = ptr->next;
	}
	ptr = *end;
	while (ptr)
	{
		free(ptr);
		ptr = ptr->next;
	}
	*end = new;
	ptr = *end;
}
