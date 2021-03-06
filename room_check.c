/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 21:21:30 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/20 20:10:34 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

bool		room_check(t_info *info, char *str)
{
	char		**split;
	t_data		*data;
	char		*for_itoa;

	split = ft_strsplit(str, ' ');
	if (!split[0] || !split[1] || !split[2] || str[0] == 'L' || str[0] == ' '\
	|| split[3] != NULL)
		error_mng(info, WRONG_ROOM_PROPERTIES, "");
	for_itoa = ft_itoa(ft_atoi(split[1]));
	if (!ft_strequ(for_itoa, split[1]))
		error_mng(info, WRONG_ROOM_PROPERTIES, for_itoa);
	ft_strdel(&for_itoa);
	for_itoa = ft_itoa(ft_atoi(split[2]));
	if (!ft_strequ(for_itoa, split[2]))
		error_mng(info, WRONG_ROOM_PROPERTIES, for_itoa);
	ft_strdel(&for_itoa);
	data = create_data(split);
	room_lst_push_back(&(info->rooms), room_lstnew(data), info);
	if (info->isend == 1)
	{
		info->end = room_lstnew(data);
		info->isend = 2;
	}
	return (TRUE);
}

bool		end_check(t_info *info)
{
	if (info->isend == 0 && info->isants && info->isstart != 1)
		info->isend = 1;
	else if (info->isstart == 1)
		error_mng(info, NO_START_ROOM, "");
	else if (info->isend == 2)
		error_mng(info, DOUBLE_END, "");
	else if (info->isend == 1)
		error_mng(info, DOUBLE_END, "");
	return (TRUE);
}

bool		start_check(t_info *info)
{
	if (info->isstart == 0 && info->isants && info->isend != 1)
		info->isstart = 1;
	else if (info->isend == 1)
		error_mng(info, NO_END_ROOM, "");
	else if (info->isstart == 1)
		error_mng(info, DOUBLE_START, "");
	else if (info->isstart == 2)
		error_mng(info, DOUBLE_START, "");
	return (TRUE);
}

bool		hashcheck(t_info *info, char *str)
{
	if (ft_strequ(str, START))
		return (start_check(info));
	else if (ft_strequ(str, END))
		return (end_check(info));
	else if (str[0] == '#')
		return (TRUE);
	return (FALSE);
}

bool		assign_start_end(t_info *info, char *str)
{
	char	**spl;

	if (hashcheck(info, str))
		return (TRUE);
	if (!hashcheck(info, str) && !ft_strchr(str, '-') && room_check(info, str))
	{
		spl = ft_strsplit(str, ' ');
		info->start = info->table[hash(spl[0])];
		info->isstart = 2;
		ft_strdel(&spl[0]);
		ft_strdel(&spl[1]);
		ft_strdel(&spl[2]);
		free(spl);
		spl = NULL;
	}
	else
		error_mng(info, NO_START_ROOM, "");
	return (TRUE);
}
