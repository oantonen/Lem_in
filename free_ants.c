/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 19:18:09 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/19 21:19:01 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

void	ant_move(t_pth *pth, int pth_len, int *end_room, int curr)
{
	int		i;

	i = pth_len - 2;
	while (i != -1)
	{
		if (pth[i].ant != 0 && i != pth_len - 2)
		{
			pth[i + 1].ant = pth[i].ant;
			ft_printf("L%d-%s ", pth[i].ant, pth[i + 1].name);
			pth[i].ant = pth[i - 1].ant;
		}
		else if (pth[i].ant != 0 && i == pth_len - 2)
		{
			ft_printf("\e[38;5;154mL%d-%s\e[m ", pth[i].ant, pth[i + 1].name);
			pth[i].ant = pth[i + 1].ant;
			*end_room += 1;
		}
		i--;
	}
	pth[0].ant = curr;
	if (curr)
		ft_printf("\e[38;5;196mL%d-%s\e[m ", curr, pth[0].name);
	if (pth_len == 1 && curr)
		*end_room += 1;
}

int		count_current_paths(int path_q, int *pth_len, int ants)
{
	int		i;
	int		curr_steps;

	i = 1;
	curr_steps = pth_len[0] + ants - 1;
	while (i < path_q)
	{
		curr_steps = curr_steps - pth_len[i];
		i++;
		if (i < path_q && curr_steps - pth_len[i] < 0)
			break ;
	}
	return (i);
}

void	free_ants(t_info *info, t_pth **pth, int *pth_len, int ants)
{
	int		i;
	int		curr;
	int		end_room;
	int		k;

	curr = 0;
	end_room = 0;
	while (end_room != info->ants)
	{
		i = count_current_paths(info->path_q, pth_len, ants - curr);
		k = 0;
		while (k != i && end_room != info->ants)
		{
			curr++;
			if (curr > ants)
				ant_move(pth[k], pth_len[k], &end_room, 0);
			else
				ant_move(pth[k], pth_len[k], &end_room, curr);
			k++;
		}
		ft_printf("\n");
	}
}
