/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_ants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:12:40 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/18 21:45:50 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

void	ant_move(t_pth *pth, int pth_len, int ants, int curr)
{
	int		i;

	i = pth_len - 2;
	// dprintf(2, "pth_len=%d\n", pth_len);
	ft_printf("\n");
	while (i != -1)
	{
		if (pth[pth_len - 1].ant == ants)
			break ;
		if ((pth)[i].ant != 0 && i != pth_len - 2)
		{
			(pth)[i + 1].ant = (pth)[i].ant;
			ft_printf("L%d-%s ", pth[i].ant, pth[i + 1].name);
			(pth)[i].ant = (pth)[i - 1].ant;
		}
		else if ((pth)[i].ant != 0 && i == pth_len - 2)
		{
			ft_printf("\e[38;5;154mL%d-%s\e[m ", pth[i].ant, pth[i + 1].name);
			(pth)[i + 1].ant += 1;
		}
		// ft_printf("L%d-%s\n", pth[i].ant, pth[i + 1].name);
		i--;
	}
}

void	free_ants(t_info *info, t_pth **pth, int *pth_len, int ants)
{
	int		i;

	i = 1;
	// dprintf(2, "Enter!\n");
	// dprintf(2, "end_ants=%d\n", pth[1][pth_len[1]].ant);
	// dprintf(2, "pth_len[0]=%d\n", pth_len[1]);
	// dprintf(2, "ants=%d\n", ants);
	while (pth[1][pth_len[1] - 1].ant < ants)
	{
		while (i != ants + 1)
		{
			pth[1][0].ant = i;
			ft_printf("\e[38;5;196mL%d-%s\e[m ", pth[1][0].ant, pth[1][0].name);
			ant_move(pth[1], pth_len[1], ants, i);
			i++;
		}
		ant_move(pth[1], pth_len[1], ants, i);
	}
	ft_printf("\n");
	free(info->pth_len);
}

void	show_arr(t_pth *arr, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		dprintf(2, "arr_name=%s\n", arr[i].name);
		dprintf(2, "arr_ant=%d\n", arr[i].ant);
		i++;
	}
}

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
				// dprintf(2, "pth[i][k].name=%s\n", pth[i][k].name);
				pth[i][k].ant = 0;
				ptr2 = ptr;
				ptr = ptr->next;
				free(ptr2);
			}
		}
	}
	// show_arr(pth[0], info->pth_len[0]);
}


















