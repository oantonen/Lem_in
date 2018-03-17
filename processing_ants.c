/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_ants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:12:40 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/17 22:03:18 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

// Lx-y Lz-w Lr-o

// L1-2
// L1-3 L2-2
// L1-1 L2-3 L3-2
// L2-1 L3-3
// L3-1

void	ant_move(t_pth **pth, int pth_len, int ants, int curr)
{
	int		i;

	i = pth_len - 2;
	while (i != 0)
	{
		if ((*pth)[i].ant != 0 && i != pth_len - 2)
		{
			(*pth)[i + 1].ant = (*pth)[i].ant;
			// ft_printf("L%d-%s", (*pth)[i].ant, (*pth)[i + 1].name);
		}
		else if ((*pth)[i].ant != 0 && i == pth_len - 2)
		{
			// ft_printf("L%d-%s", (*pth)[i].ant, (*pth)[i + 1].name);
			(*pth)[i + 1].ant += 1;
		}
		ft_printf("L%d-%s", (*pth)[i].ant, (*pth)[i + 1].name);
		i--;
	}
}

void	free_ants(t_info *info, t_pth **pth, int *pth_len, int ants)
{
	int		i;

	i = 0;
	// dprintf(2, "Enter!\n");
	// dprintf(2, "end_ants=%d\n", pth[1][pth_len[1]].ant);
	// dprintf(2, "pth_len[0]=%d\n", pth_len[1]);
	// dprintf(2, "ants=%d\n", ants);
	// while (pth[0][pth_len[0] - 1].ant < ants)
	// {
	// 	while (i != ants + 1)
	// 		i++;
	// 	ant_move(&pth[0], pth_len[0], ants, i);
	// }

}


// void	free_ants(t_info *info, t_list **paths)
// {
// 	int		ants;
// 	t_list	*room;
// 	int		i;

// 	ants = 1;
// 	while (ants != info->ants + 1)
// 	{
// 		room = info->paths[1];
// 		i = 0;
// 		while (room)
// 		{
// 			if (i == 0)
// 				ft_printf("\e[38;5;196mL%d-%s\e[m", ants, ((t_data*)room->content)->name);
// 			else if (room->next == NULL)
// 				ft_printf("\e[38;5;154mL%d-%s\e[m", ants, ((t_data*)room->content)->name);
// 			else
// 				ft_printf("L%d-%s", ants, ((t_data*)room->content)->name);
// 			ft_printf(" ");
// 			room = room->next;
// 			i++;
// 		}
// 		ft_printf("\n");
// 		ants++;
// 	}
// }

// '\e[1;34m%-6s\e[m' "This is text"
 // ESC[38;5;#m
void	show_arr(t_pth *arr, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		// dprintf(2, "arr_name=%s\n", arr[i].name);
		i++;
	}
}

void	count_rooms(t_list *path, int *rooms)
{
	t_list *ptr;
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

void	transform_paths(t_info *info, t_list **paths, t_pth **pth)
{
	int		rooms;
	int		i;
	int		k;
	t_list	*ptr;
	
	i = -1;
	pth = (t_pth**)malloc(sizeof(t_pth*) * (info->path_q + 1));
	info->pth_len = (int*)malloc(sizeof(int) * info->path_q);
	pth[info->path_q] = NULL;
	while (++i < info->path_q)
	{
		k = 0;
		ptr = info->paths[i];
		count_rooms(ptr, &rooms);
		info->pth_len[i] = rooms;
		// dprintf(2, "rooms=%d\n", rooms);
		pth[i] = (t_pth*)malloc(sizeof(t_pth) * (rooms + 1));
		pth[rooms] = NULL;
		while (k < rooms)
		{
			pth[i][k].name = ((t_data*)ptr->content)->name;
			// dprintf(2, "((t_data*)ptr->content)->name=%s\n", ((t_data*)ptr->content)->name);
			pth[i][k].ant = 0;
			ptr = ptr->next;
			k++;
		}
	}
	show_arr(pth[0], info->pth_len[0]);
}


















