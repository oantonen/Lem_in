/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 19:18:09 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/20 20:16:45 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

void	print_paths(t_info *info, t_pth **pth, int *pth_len, int path_q)
{
	int		k;
	int		i;
	int		y;

	i = 220;
	y = 0;
	if (info->argv[1] && ft_strequ(info->argv[1], "-p"))
	{
		while (y < path_q)
		{
			k = 0;
			ft_printf("\e[38;5;214m[%s] %s\e[m ", info->start->d->name, \
				"---->");
			while (k < pth_len[y])
			{
				ft_printf("[\e[38;5;%dm%s\e[m] ", i - 6 * y, pth[y][k].name);
				if (k + 1 != pth_len[y])
					ft_printf("\e[38;5;%dm%s\e[m ", i - 6 * y, "---->");
				k++;
			}
			y++;
			ft_putendl("");
		}
		ft_putendl("");
	}
}

void	ant_move(t_pth *pth, int pth_len, int *end_room, int curr)
{
	int		i;

	i = pth_len - 1;
	while (--i != -1)
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
	}
	if (curr && pth_len != 1)
		ft_printf("\e[38;5;196mL%d-%s\e[m ", pth[0].ant = curr, pth[0].name);
	if (pth_len == 1 && curr)
	{
		ft_printf("\e[38;5;154mL%d-%s\e[m ", curr, pth[0].name);
		*end_room += 1;
	}
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
	while (end_room != ants)
	{
		i = count_current_paths(info->path_q, pth_len, ants - curr);
		k = 0;
		while (k != i && end_room != info->ants)
		{
			curr++;
			if (curr + pth_len[info->path_q - 1] >= ants)
				i = info->path_q;
			if (curr > ants)
				ant_move(pth[k], pth_len[k], &end_room, 0);
			else
				ant_move(pth[k], pth_len[k], &end_room, curr);
			k++;
		}
		ft_putendl("");
	}
}
