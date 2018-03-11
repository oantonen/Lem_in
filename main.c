/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 20:04:37 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/11 17:59:48 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

unsigned int	hash(char *str)
{
	unsigned long	code;

	code = 0;
	while (*str)
	{
		code = *str + (code << 6) + (code << 10) - code;
		str++;
	}
	return (code & 524287);
}

bool		error_mng(t_info *info, int err_nb, char *s)
{
		// ft_printf("ERROR\n");
		// exit(EXIT_FAILURE);
	if (err_nb == DOUBLE_START)
		ft_printf("Error: duplicated start.\n");
	else if (err_nb == DOUBLE_END)
		ft_printf("Error: duplicated end.\n");
	else if (err_nb == NOT_OK)
		ft_printf("Error: noncompliant line.\n");
	else if (err_nb == INVALID_ANTS)
		ft_printf("Error: incorrect format for ants.\n");
	else if (err_nb == EMPTY_LINE)
		ft_printf("Error: the entered line is empty.\n");
	else if (err_nb == WRONG_ROOM_PROPERTIES)
		ft_printf("Error: wrong room's properties.\n");
	else if (err_nb == DUPLICATED_ROOM)
		ft_printf("Error: room with such name already exist.\n");
	else if (err_nb == DUPLICATED_COORDINATES)
		ft_printf("Error: room's coordinates is duplicated.\n");
	else if (err_nb == ROOM_NOT_FOUND)
		ft_printf("Error: room with the name \"%s\" doesn't exist.\n", s);
	else if (err_nb == START_END_MISSING)
		ft_printf("Error: found no room for start or end.\n", s);
	else if (err_nb == NO_START_ROOM)
		ft_printf("Error: start room not found.\n", s);
	else if (err_nb == NO_END_ROOM)
		ft_printf("Error: end room not found.\n", s);
	else if (err_nb == INVALID_LINK)
		ft_printf("Error: invalid link format.\n", s);
	// else
	// 	return (1);
	//clear leaks
	exit(EXIT_FAILURE);
	return (FALSE);
}

void	put_room_to_table(t_rm_list **table, t_rm_list *new)
{
	unsigned int i;

	i = new->d->h;

	if (!table[i])
		table[i] = new;
	else if (table[i])
	{
		while(table[i]->same_h)
			table[i] = table[i]->same_h;
		table[i]->same_h = new;
	}
}

int		main(int argc, char **argv)
{
	char	*first;
	t_list	*begin;
	t_info	info;

	info = INITIALIZE;
	info.e_errors = OK;
	info.rooms = NULL;
	begin = NULL;
	info.table = (t_rm_list**)malloc(sizeof(t_rm_list*) * 524287);
	ft_memset(info.table, 0, 524287 * sizeof(t_rm_list*));
	while (get_next_line(0, &first) > 0)
	{
		// dprintf(2, "%s\n", first);
		if (check_line(&info, first) == 1)
			li_lst_push_back(&begin, ft_lstnew(first, 0));
		else
			error_mng(&info, NOT_OK, "");
		// ft_strdel(&first);
	}
	// ft_putstr("\n");
	// while (begin)
	// {
	// 	ft_printf("%s\n", begin->content);
	// 	begin = begin->next;
	// }
	// if (info.start)
	// 	ft_printf("start=%s\n", info.start->d->name);
	// if (info.end)
	// 	ft_printf("end=%s\n", info.end->d->name);
	while (info.rooms)
	{
		if (info.table[info.rooms->d->h]->d->link)
		{
			printf("name1=%s ->", info.table[info.rooms->d->h]->d->name);
			while (info.table[info.rooms->d->h]->d->link)
			{
				printf("name2=%s\n", info.table[info.rooms->d->h]->d->link->name);
				info.table[info.rooms->d->h]->d = info.table[info.rooms->d->h]->d->link;
			}
			
		}
		info.rooms = info.rooms->next;
	}
	
	return (0);
}
