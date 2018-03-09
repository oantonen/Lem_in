/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 21:21:30 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/08 22:06:46 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

int		room_check(t_info *info, char *str)
{
	char	**split;

	split = ft_strsplit(str, ' ');
	if (!split[0] || !split[1] || !split[2])
		error_mng(info, WRONG_ROOM_PROPERTIES, "");
	if (str[0] == 'L')
		error_mng(info, WRONG_ROOM_PROPERTIES, "");
	if (!ft_strequ(ft_itoa(ft_atoi(split[1])), split[1]))
			error_mng(info, WRONG_ROOM_PROPERTIES, "");
	if (!ft_strequ(ft_itoa(ft_atoi(split[2])), split[2]))
			error_mng(info, WRONG_ROOM_PROPERTIES, "");
	room_lst_push_back(&(info->rooms), room_lstnew(split), info);
	if (info->isend == 1)
	{
		info->end = room_lstnew(split);
		info->isend = 2;
	}
	return (1);
}

int		end_check(t_info *info)
{
	if (info->isend == 0 && info->isants && info->isstart != 1)
		info->isend = 1;
	else if (info->isstart == 1)
		error_mng(info, NO_START_ROOM, "");
	else if (info->isend == 2)
		error_mng(info, DOUBLE_END, "");
	else if (info->isend == 1)
		error_mng(info, DOUBLE_END, "");
	return (1);
}

int		start_check(t_info *info)
{
	if (info->isstart == 0 && info->isants && info->isend != 1)
		info->isstart = 1;
	else if (info->isend == 1)
		error_mng(info, NO_END_ROOM, "");
	else if (info->isstart == 1)
		error_mng(info, DOUBLE_START, "");
	else if (info->isstart == 2)
		error_mng(info, DOUBLE_START, "");
	return (1);
}

int		hashcheck(t_info *info, char *str)
{
	if (ft_strequ(str, START))
		return (start_check(info));
	else if (ft_strequ(str, END))
		return (end_check(info));
	else if (str[0] == '#')
		return (1);
	return (0);
}

int		assign_start_end(t_info *info, char *str)
{
	if (hashcheck(info, str))
		return (1);
	if (!hashcheck(info, str) && !ft_strchr(str, '-') && room_check(info, str))
	{
		info->start = room_lstnew(ft_strsplit(str, ' '));
		info->isstart = 2;
	}
	else
		error_mng(info, NO_START_ROOM, "");
	return (1);
}
