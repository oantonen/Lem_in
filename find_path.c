/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 23:20:03 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/13 21:37:27 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

void	save_last_rooms(t_data *save, t_rm_list *end, int level)
{
	t_list	*ptr;

	ptr = end->d->link;
	while (ptr)
	{
		if (ft_strequ(((t_data*)ptr->content)->name, save->name))
			ptr->content_size = level;
		ptr = ptr->next;
	}
}

void	bfs_path(t_info *info, t_rm_list **table)
{
	t_list	*q;
	t_list	*ptr;
	t_list	*ptr2;

	q = ft_lstnew(info->table[info->start->d->h]->d, 0);
	((t_data*)q->content)->level = 0;
	while (q)
	{
		ptr = ((t_data*)q->content)->link;
		while (ptr)
		{
			if (((t_data*)ptr->content)->level == -1)
			{
				// dprintf(2, "link->name=%s\n", ((t_data*)ptr->content)->name);
				li_lst_push_back(&q, ptr2 = ft_lstnew(ptr->content, 0));
				((t_data*)ptr2->content)->level = ((t_data*)q->content)->level + 1;
			}
			if (ft_strequ(((t_data*)ptr->content)->name, info->end->name))
				save_last_rooms(((t_data*)ptr->content), info->end, ((t_data*)q->content)->level + 1);
			ptr = ptr->next;
		}
		ptr = q->next;
		free(q);
		q = ptr;
	}
	if (info->end->d->level == -1)
		error_mng(info, NO_PATH, "");
	dprintf(2, "end_name=%s\n", info->end->d->name);
	dprintf(2, "end_level=%d\n", info->end->d->level);
}

void	save_path(t_info *info, t_rm_list *end)
{

}
