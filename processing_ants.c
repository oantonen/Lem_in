/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_ants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:12:40 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/19 20:09:06 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

// void	show_arr(t_pth *arr, int len)
// {
// 	int		i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		dprintf(2, "arr_name=%s\n", arr[i].name);
// 		dprintf(2, "arr_ant=%d\n", arr[i].ant);
// 		i++;
// 	}
// }

void	count_real_pathes(t_info *info, t_list **paths)
{
	int		q;
	int		i;

	q = 0;
	i = 0;
	while (info->path_q > i)
	{
		if (paths[i])
			q++;
		i++;
	}
	info->path_q = q;
}

void	count_rooms(t_list *path, int *rooms)
{
	t_list	*ptr;
	int		i;

	i = 0;
	ptr = path;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	*rooms = i;
}

void	transform_paths(t_info *info, t_list **paths, t_pth **pth, t_list *ptr2)
{
	int		rooms;
	int		i;
	int		k;
	t_list	*ptr;

	i = -1;
	info->pth_len = (int*)ft_memalloc(sizeof(int) * info->path_q);
	while (++i < info->path_q)
	{
		k = -1;
		if ((ptr = info->paths[i]) != NULL)
		{
			count_rooms(ptr, &rooms);
			info->pth_len[i] = rooms;
			pth[i] = (t_pth*)ft_memalloc(sizeof(t_pth) * (rooms));
			while (++k < rooms)
			{
				pth[i][k].name = ((t_data*)ptr->content)->name;
				pth[i][k].ant = 0;
				ptr2 = ptr;
				ptr = ptr->next;
				free(ptr2);
			}
		}
	}	// show_arr(pth[0], info->pth_len[0]);
}
