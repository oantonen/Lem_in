/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 23:20:03 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/16 12:16:49 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

t_list	*save_paths(t_info *info, t_list *ptr, t_list *new)
{
	t_list	*ptr2;

	// dprintf(2, "ptr_name_first=%s\n", ((t_data*)ptr->content)->name);
	if (new == NULL)
		ft_lstadd(&new, ft_lstnew((info->end->d), 0));
	ptr2 = ((t_data*)ptr->content)->link;
	while (((t_data*)ptr->content)->level != 0)
	{
		if (((t_data*)ptr->content)->level - 1 == ((t_data*)ptr2->content)->level)
		{
			ft_lstadd(&new, ft_lstnew(((t_data*)ptr->content), 0));
			((t_data*)ptr->content)->level = -1;
			return (save_paths(info, ptr2, new));
		}
		else
		{
			ptr2 = ptr2->next;
		}
	}
	ft_lstadd(&new, ft_lstnew(info->start->d, 0));
	// while (new)
	// {
		// dprintf(2, "save_paths | cont_size=%zu\n", new->content_size);
	// 	dprintf(2, "save_paths | name=%s\n", ((t_data*)new->content)->name);
	// 	new = new->next;
	// }
	return (new);
}

void	count_paths(t_info *info, t_rm_list *end)
{
	t_list	*ptr;
	t_list	*new;
	int		i;

	i = 0;
	ptr = end->d->link;
	// ft_lstadd(&end->d->link, ft_lstnew(end->d, 0));
	while (ptr)
	{
		if (ptr->content_size != 0)
			info->path_q++;
		ptr = ptr->next;
	}
	info->paths = (t_list**)malloc(sizeof(t_list*) * (info->path_q + 1));
	info->paths[info->path_q] = NULL;
	if (info->path_q >= 2)
		sort_end_links(&end->d->link);
	ptr = end->d->link;
	while (ptr)
	{
		new = NULL;
		info->paths[i] = save_paths(info, ptr, new);
		i++;
		ptr = ptr->next;
	}
	ptr = info->paths[1];
	while (ptr)
	{
		dprintf(2, "save_paths | name=%s\n", ((t_data*)ptr->content)->name);
		ptr = ptr->next;
	}
	dprintf(2, "path_q=%d\n", info->path_q);
}

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
			if (ft_strequ(((t_data*)ptr->content)->name, info->end->d->name))
				save_last_rooms(((t_data*)q->content), info->end, ((t_data*)q->content)->level + 1);
			ptr = ptr->next;
		}
		ptr = q->next;
		free(q);
		q = ptr;
	}
	if (info->end->d->level == -1)
		error_mng(info, NO_PATH, "");
	count_paths(info, info->end);
}


