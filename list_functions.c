/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 23:03:32 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/13 14:34:52 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

t_data	*create_data(char **split)
{
	t_data	*data;

	data = (t_data*)malloc(sizeof(t_data));
	data->name = split[0];
	data->x = ft_atoi(split[1]);
	data->y = ft_atoi(split[2]);
	data->level = -1;
	data->h = hash(split[0]);
	data->link = NULL;
	return (data);
}

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

t_rm_list	*room_lstnew(t_data *data)
{
	t_rm_list	*new;

	if (!(new = (t_rm_list*)malloc(sizeof(t_rm_list))))
		return (NULL);
	new->d = data;
	new->next = NULL;
	new->same_h = NULL;
	return (new);
}

void	room_check2(t_info *info, t_data *data1, t_data	*data2)
{
	if (ft_strequ(data1->name, data2->name))
		error_mng(info, DUPLICATED_ROOM, "");
	if (data1->x == data2->x && data1->y == data2->y)
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
			room_check2(info, ptr->d, new->d);
			while (ptr->next != NULL)
			{
				room_check2(info, ptr->d, new->d);
				ptr = ptr->next;
			}
			ptr->next = new;
		}
	}
	put_room_to_table(info->table, new);
}
