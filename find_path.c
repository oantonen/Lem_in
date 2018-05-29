/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 23:20:03 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/20 16:02:14 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

int		save_paths(t_info *info, t_list *ptr, t_list **new)
{
	t_list	*ptr2;

	if (((t_data*)ptr->content)->lvl == 0)
		return (1);
	ptr2 = ((t_data*)ptr->content)->link;
	while (ptr2)
	{
		if (((t_data*)ptr->content)->lvl - 1 == ((t_data*)ptr2->content)->lvl \
			&& save_paths(info, ptr2, new))
		{
			li_lst_push_back(new, ft_lstnew(((t_data*)ptr->content), 0));
			((t_data*)ptr->content)->lvl = -1;
			return (1);
		}
		else
			ptr2 = ptr2->next;
	}
	return (0);
}

void	count_paths(t_info *info, t_rm_list *end, int i)
{
	t_list	*ptr;
	t_list	*new;

	ptr = end->d->link;
	while (ptr)
	{
		if (ptr->content_size != 0)
			info->path_q++;
		ptr = ptr->next;
	}
	info->paths = (t_list**)ft_memalloc(sizeof(t_list*) * (info->path_q));
	if (info->path_q >= 2)
		sort_end_links(&end->d->link);
	ptr = end->d->link;
	while (ptr)
	{
		new = NULL;
		if (ptr->content_size != 0 && save_paths(info, ptr, &new))
		{
			li_lst_push_back(&new, ft_lstnew((info->end->d), 0));
			info->paths[i++] = new;
		}
		ptr = ptr->next;
	}
}

void	save_last_rooms(t_list *q, t_rm_list *end, int lvl)
{
	t_list	*ptr;
	t_data	*save;

	save = ((t_data*)q->content);
	ptr = end->d->link;
	while (ptr)
	{
		if (ft_strequ(((t_data*)ptr->content)->name, save->name))
		{
			ptr->content_size = lvl;
			break ;
		}
		ptr = ptr->next;
	}
	end->d->lvl = 1;
}

void	add_queue(t_info *info, t_list **q, t_list *ptr)
{
	t_list *ptr2;

	while (ptr)
	{
		if (((t_data*)ptr->content)->lvl == -1 && \
			!ft_strequ(((t_data*)ptr->content)->name, info->end->d->name))
		{
			li_lst_push_back(q, ptr2 = ft_lstnew(ptr->content, 0));
			((t_data*)ptr2->content)->lvl = ((t_data*)(*q)->content)->lvl + 1;
		}
		if (ft_strequ(((t_data*)ptr->content)->name, info->end->d->name))
			save_last_rooms(*q, info->end, ((t_data*)(*q)->content)->lvl + 1);
		ptr = ptr->next;
	}
}

void	bfs_path(t_info *info, t_rm_list **table)
{
	t_list	*q;
	t_list	*ptr;
	t_list	*ptr2;

	q = ft_lstnew(info->table[info->start->d->h]->d, 0);
	((t_data*)q->content)->lvl = 0;
	while (q)
	{
		ptr = ((t_data*)q->content)->link;
		add_queue(info, &q, ptr);
		ptr = q->next;
		free(q);
		q = ptr;
	}
	free(q);
	count_paths(info, info->end, 0);
}
