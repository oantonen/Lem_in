/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 20:04:37 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/18 21:44:48 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

unsigned int	hash(char *str)
{
	unsigned long	code;

	code = 0;
	// dprintf(2, "str==%s\n", str);
	while (*str)
	{
		code = ((*str << 2) ^ 75379) + (code << 6) + (code << 4) - code;
		str++;
	}
	// dprintf(2, "code=%lu\n", code);
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
	else if (err_nb == NO_PATH)
		ft_printf("Error: there is no path at this farm.\n", s);
	if (*s)
		ft_strdel(&s);
	// else
	// 	return (1);
	//clear leaks
	while(1);
	exit(EXIT_FAILURE);
	return (FALSE);
}
void	before_start(t_info *info, t_list **begin)
{
	*info = INITIALIZE;
	info->e_errors = OK;
	info->rooms = NULL;
	*begin = NULL;
	info->table = (t_rm_list**)malloc(sizeof(t_rm_list*) * 524287);
	ft_memset(info->table, 0, 524287 * sizeof(t_rm_list*));
}

void	graph_and_co(t_info *info, t_rm_list **table)
{
	t_pth	**pth;
	t_list	*ptr31;
	int		i;

	bfs_path(info, info->table);
	if (info->path_q == 0)
		error_mng(info, NO_PATH, "");
	i = info->path_q;
	count_real_pathes(info, info->paths);
	pth = (t_pth**)malloc(sizeof(t_pth*) * (info->path_q));
	transform_paths(info, info->paths, pth, ptr31);
	free_ants(info, pth, info->pth_len, info->ants);
	while (--info->path_q != -1)
		free(pth[info->path_q]);
	free(pth);
}

int		main(int argc, char **argv)
{
	char	*first;
	t_list	*begin;
	t_info	info;
	t_list  *ptr;

	before_start(&info, &begin);
	while (get_next_line(0, &first) > 0)
	{
		// dprintf(2, "%s\n", first);
		if (check_line(&info, first) == 1)
			li_lst_push_back(&begin, ft_lstnew(first, 0));
		else
			error_mng(&info, NOT_OK, "");
	}
	graph_and_co(&info, info.table);
	system("leaks lem-in");
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
	// while (info.rooms)
	// {
	// 	if (info.table[info.rooms->d->h]->d->link)
	// 	{
	// 		printf("name1=%s ->\n", info.table[info.rooms->d->h]->d->name);
	// 		while (info.table[info.rooms->d->h]->d->link)
	// 		{
	// 			printf("name2=%s\n", ((t_data*)info.table[info.rooms->d->h]->d->link->content)->name);
	// 			info.table[info.rooms->d->h]->d->link = info.table[info.rooms->d->h]->d->link->next;
	// 			// if (info.table[info.rooms->d->h]->d->link)
	// 			// printf("name2=%s\n", ((t_data*)info.table[info.rooms->d->h]->d->link->content)->name);
	// 		}
			
	// 	}
	// 	info.rooms = info.rooms->next;
	// }
	// int i = 0;
	// while (info.table[i])
	// {
	// 	free(info.table[i]);
	// 	i++;
	// }
	// free(info.table);
	return (0);
}
