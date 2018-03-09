/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 23:03:32 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/08 21:30:13 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

// t_list	*li_lstnew(char *first)
// {
// 	t_list	*new;

// 	if (!(new = (t_list*)malloc(sizeof(t_list))))
// 		return (NULL);
// 	new->content = first;
// 	new->next = NULL;
// 	return (new);
// }

void	li_lst_push_back(t_list **begin_list, t_list *new)
{
	t_list	*ptr;

	ptr = NULL;
	if (begin_list)
	{
		if (*begin_list == NULL)
		{
			*begin_list = new;
			(*begin_list)->next = NULL;
		}
		else
		{
			ptr = *begin_list;
			while (ptr->next != NULL)
				ptr = ptr->next;
			ptr->next = new;
		}
	}
}

t_rm_list	*room_lstnew(char **split)
{
	t_rm_list	*new;

	if (!(new = (t_rm_list*)malloc(sizeof(t_rm_list))))
		return (NULL);
	new->name = split[0];
	new->x = ft_atoi(split[1]);
	new->y = ft_atoi(split[2]);
	new->h = hash(split[1]);
	new->next = NULL;
	return (new);
}

void	room_check2(t_info *info, t_rm_list	*ptr, t_rm_list	*new)
{
	if (ft_strequ(ptr->name, new->name))
		error_mng(info, DUPLICATED_ROOM, "");
	if (ptr->x == new->x && ptr->y == new->y)
		error_mng(info, DUPLICATED_COORDINATES, "");
}

void	room_lst_push_back(t_rm_list **begin_list, t_rm_list *new, t_info *info)
{
	t_rm_list	*ptr;

	ptr = NULL;
	if (begin_list)
	{
		if (*begin_list == NULL)
			*begin_list = new;
		else
		{
			ptr = *begin_list;
			room_check2(info, ptr, new);
			while (ptr->next != NULL)
			{
				// dprintf(2, "push_back=%s\n", ptr->name);
				room_check2(info, ptr, new);
				ptr = ptr->next;
			}
			ptr->next = new;
		}
	}
}

void	room_add_lst(t_rm_list **begin, t_rm_list *new)
{
	if (begin && new)
	{
		new->next = *begin;
		*begin = new;
	}
}
