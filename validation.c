/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 15:59:53 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/10 22:40:11 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

int		put_links(t_rm_list **table, t_rm_list *r1, t_rm_list *r2)
{
	// t_rm_list	*ptr;
	// t_rm_list	*ptr2;

	// ptr = table[r1->h];
	// ptr2 = table[r2->h];


}

int		check_links(t_info *info, char *str, t_rm_list *r1, t_rm_list *r2)
{
	char		**split;
	t_rm_list	*ptr;

	info->only_links = 1;
	if (info->isstart != 2 || info->isend != 2)
		error_mng(info, START_END_MISSING, "");
	split = ft_strsplit(str, '-');
	ptr = info->rooms;
	if (split[0] && split[1])
		while (ptr)
		{
			if (ft_strequ(ptr->name, split[0]))
				r1 = ptr;
			if (ft_strequ(ptr->name, split[1]))
				r2 = ptr;
			ptr = ptr->next;
		}
	if (!r1)
		error_mng(info, ROOM_NOT_FOUND, split[0]);
	if (!r2)
		error_mng(info, ROOM_NOT_FOUND, split[1]);
	put_links(info->table, r1, r2);
	return (1);
}

int		ant_check(t_info *info, char *str)
{
	int		i;

	i = 0;
	if (!ft_strequ(ft_itoa(ft_atoi(str)), str))
		error_mng(info, INVALID_ANTS, "");
	if (ft_atoi(str) > 0 && info->isants == 0)
	{
		info->ants = ft_atoi(str);
		info->isants = 1;
	}
	else
		error_mng(info, INVALID_ANTS, "");
	return (1);
}

int		check_line(t_info *info, char *str)
{
	if (*str == '\0')
		error_mng(info, EMPTY_LINE, "");
	else if (info->isstart == 1)
		return (assign_start_end(info ,str));
	else if (str[0] != '#' && info->isants == 0 && ant_check(info, str))
		return (1);
	else if (str[0] == '#' && hashcheck(info, str))
		return (1);
	else if (info->only_links && !ft_strchr(str, '-'))
		error_mng(info, INVALID_LINK, "");
	else if (!info->only_links && !ft_strchr(str, '-') && room_check(info, str))
		return (1);
	else if (ft_strchr(str, '-') && check_links(info, str, info->r1, info->r2))
		return (1);
	
	return (0);
}
