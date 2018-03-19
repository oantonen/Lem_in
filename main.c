/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 20:04:37 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/19 20:18:51 by oantonen         ###   ########.fr       */
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

void		print_usage(t_info *info)
{
	ft_putendl("usage:\n");
	ft_putendl(" - You should make an input in the following format:");
	ft_putendl(" - number_of_ants\nthe_rooms\nthe_links\n");
	ft_putendl(" - Number of ants must be positive integer up to MAX_INT.\n");
	ft_putendl(" - The rooms line must have unique name and 2 coordinates \
		separeted by 'space'.\n");
	ft_putendl(" - In the room's name it isn't alowed to use '-', 'L', '#'.\n");
	ft_putendl(" - Rooms must have start && end rooms, which can be \
		distinguished by commands '##start', '##end' .\n");
	ft_putendl(" - You can put any comments starting with '#'.\n");
	ft_putendl(" - In the linking part you should put links to inserted rooms \
		by which ants will be moving.\n");
	ft_putendl(" - The entered ant's farm must have one or more possible paths\
		.\n");
	ft_putendl("\e[38;5;196m - Enjoy!\n\e[m");
	exit(0);
}

void		print_errors(int err_nb, char *s)
{
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
}

bool		error_mng(t_info *info, int err_nb, char *s)
{
	if (info->argv[1] && ft_strequ(info->argv[1], "-d"))
	{
		print_errors(err_nb, s);
		if (err_nb == INVALID_LINK)
			ft_printf("Error: invalid link format.\n", s);
		else if (err_nb == NO_PATH)
			ft_printf("Error: there is no path at this farm.\n", s);
		if (*s)
			ft_strdel(&s);
		exit(EXIT_FAILURE);
	}
	ft_printf("ERROR\n");
	exit(EXIT_FAILURE);
	//clear leaks
	return (FALSE);
}
void	before_start(t_info *info, t_list **begin, char **argv)
{
	if (argv[1] && ft_strequ(argv[1], "-h"))
		print_usage(info);
	*info = INITIALIZE;
	info->argv = argv;
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
	// int		i;

	bfs_path(info, info->table);
	if (info->path_q == 0)
		error_mng(info, NO_PATH, "");
	// i = info->path_q;
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

	before_start(&info, &begin, argv);
	while (get_next_line(0, &first) > 0)
	{
		// dprintf(2, "%s\n", first);
		if (check_line(&info, first) == 1)
			li_lst_push_back(&begin, ft_lstnew(first, 0));
		else
			error_mng(&info, NOT_OK, "");
	}
	while (begin)
	{
		ft_printf("%s\n", begin->content);
		free(begin->content);
		ptr = begin;
		begin = begin->next;
		free(ptr);
	}
	ft_putstr("\n");
	
	graph_and_co(&info, info.table);
	// system("leaks lem-in");
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
