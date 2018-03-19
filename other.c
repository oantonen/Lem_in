/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 21:58:44 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/19 22:26:29 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

unsigned	hash(char *str)
{
	unsigned long	code;

	code = 0;
	while (*str)
	{
		code = ((*str << 2) ^ 75379) + (code << 2) + (code << 4) - code;
		str++;
	}
	return (code & 524287);
}

void		print_usage(t_info *info)
{
	ft_putendl("usage:\n");
	ft_putendl(" - You should make an input in the following format:");
	ft_putendl("\tnumber_of_ants\n\tthe_rooms\n\tthe_links");
	ft_putendl(" - Number of ants must be positive integer up to MAX_INT.");
	ft_putendl(" - The rooms line must have unique name and 2 coordinates \
separeted by 'space'.");
	ft_putendl(" - In the room's name it isn't alowed to use '-', 'L', '#'.");
	ft_putendl(" - Rooms must have start && end rooms, which can be \
distinguished by commands '##start', '##end' .");
	ft_putendl(" - You can put any comments starting with '#'.");
	ft_putendl(" - In the linking part you should put links to inserted rooms \
by which ants will be moving.");
	ft_putendl(" - The entered ant's farm must have one or more possible paths\
.");
	ft_putendl("\e[38;5;202m - Enjoy!\e[m");
	exit(0);
}

void		print_errors(int err_nb, char *s)
{
	if (err_nb == DOUBLE_START)
		ft_putstr_fd("Error: duplicated start.\n", 2);
	else if (err_nb == DOUBLE_END)
		ft_putstr_fd("Error: duplicated end.\n", 2);
	else if (err_nb == NOT_OK)
		ft_putstr_fd("Error: noncompliant line.\n", 2);
	else if (err_nb == INVALID_ANTS)
		ft_putstr_fd("Error: incorrect format for ants.\n", 2);
	else if (err_nb == EMPTY_LINE)
		ft_putstr_fd("Error: the entered line is empty.\n", 2);
	else if (err_nb == WRONG_ROOM_PROPERTIES)
		ft_putstr_fd("Error: wrong room's properties.\n", 2);
	else if (err_nb == DUPLICATED_ROOM)
		ft_putstr_fd("Error: room with such name already exist.\n", 2);
	else if (err_nb == DUPLICATED_COORDINATES)
		ft_putstr_fd("Error: room's coordinates is duplicated.\n", 2);
	else if (err_nb == ROOM_NOT_FOUND)
		ft_printf("Error: room with the name \"%s\" doesn't exist.\n", s);
	else if (err_nb == START_END_MISSING)
		ft_putstr_fd("Error: found no room for start or end.\n", 2);
	else if (err_nb == NO_START_ROOM)
		ft_putstr_fd("Error: start room not found.\n", 2);
	else if (err_nb == NO_END_ROOM)
		ft_putstr_fd("Error: end room not found.\n", 2);
}

bool		error_mng(t_info *info, int err_nb, char *s)
{
	if (info->argv[1] && ft_strequ(info->argv[1], "-d"))
	{
		print_errors(err_nb, s);
		if (err_nb == INVALID_LINK)
			ft_putstr_fd("Error: invalid link format.\n", 2);
		else if (err_nb == NO_PATH)
			ft_putstr_fd("Error: there is no path at this farm.\n", 2);
		if (*s)
			ft_strdel(&s);
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd("ERROR\n", 2);
	exit(EXIT_FAILURE);
	return (FALSE);
}
