/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 15:59:53 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/19 22:27:48 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

int		put_links(t_rm_list **table, t_rm_list *r1, t_rm_list *r2)
{
	t_rm_list	*ptr;
	t_rm_list	*ptr2;
	t_list		*new;

	ptr = table[r1->d->h];
	ptr2 = table[r2->d->h];
	new = ft_lstnew(ptr2->d, 0);
	if (ptr->same_h == NULL && ptr2->same_h == NULL)
	{
		ft_lstadd(&(ptr->d->link), new);
		ft_lstadd(&(ptr2->d->link), ft_lstnew(ptr->d, 0));
	}
	else
	{
		while (ptr->same_h && !ft_strequ(ptr->d->name, r1->d->name))
			ptr = ptr->same_h;
		ft_lstadd(&(ptr->d->link), new);
		while (ptr2->same_h && !ft_strequ(ptr2->d->name, r2->d->name))
			ptr2 = ptr2->same_h;
		ft_lstadd(&(ptr2->d->link), ft_lstnew(ptr->d, 0));
	}
	return (TRUE);
}

void	put_room_to_table(t_rm_list **table, t_rm_list *new)
{
	unsigned int i;

	i = new->d->h;
	if (!table[i])
		table[i] = new;
	else if (table[i])
	{
		while (table[i]->same_h)
			table[i] = table[i]->same_h;
		table[i]->same_h = new;
	}
}

int		check_links(t_info *info, char *str)
{
	char		**split;
	t_rm_list	*ptr;

	info->only_links = 1;
	if (info->isstart != 2 || info->isend != 2)
		error_mng(info, START_END_MISSING, "");
	split = ft_strsplit(str, '-');
	ptr = info->rooms;
	if (split[0] && split[1])
	{
		info->r1 = info->table[hash(split[0])];
		info->r2 = info->table[hash(split[1])];
	}
	if (!info->r1)
		error_mng(info, ROOM_NOT_FOUND, ft_strdup(split[0]));
	if (!info->r2)
		error_mng(info, ROOM_NOT_FOUND, ft_strdup(split[1]));
	ft_strdel(&split[0]);
	ft_strdel(&split[1]);
	free(split);
	split = NULL;
	put_links(info->table, info->r1, info->r2);
	return (TRUE);
}

int		ant_check(t_info *info, char *str)
{
	int		i;
	char	*for_itoa;

	i = 0;
	for_itoa = ft_itoa(ft_atoi(str));
	if (!ft_strequ(for_itoa, str))
		error_mng(info, INVALID_ANTS, "");
	ft_strdel(&for_itoa);
	if (ft_atoi(str) > 0 && info->isants == 0)
	{
		info->ants = ft_atoi(str);
		info->isants = 1;
	}
	else
		error_mng(info, INVALID_ANTS, "");
	return (TRUE);
}

int		check_line(t_info *info, char *str)
{
	if (*str == '\0')
		error_mng(info, EMPTY_LINE, "");
	else if (info->isstart == 1)
		return (assign_start_end(info, str));
	else if (str[0] != '#' && info->isants == 0 && ant_check(info, str))
		return (TRUE);
	else if (str[0] == '#' && hashcheck(info, str))
		return (TRUE);
	else if (info->only_links && !ft_strchr(str, '-'))
		error_mng(info, INVALID_LINK, "");
	else if (!info->only_links && !ft_strchr(str, '-') && room_check(info, str))
		return (TRUE);
	else if (ft_strchr(str, '-') && check_links(info, str))
		return (TRUE);
	return (FALSE);
}
