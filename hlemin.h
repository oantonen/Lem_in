/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hlemin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 11:57:13 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/09 18:01:05 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HLEMIN_H
# define HLEMIN_H

# include "hprintf.h"
#include <stdio.h> ////

typedef enum			e_type
{
	OK, DOUBLE_START, DOUBLE_END, NOT_OK, INVALID_ANTS, WRONG_ROOM_PROPERTIES, 
	ANT_IS_MISSING, DUPLICATED_ROOM, DUPLICATED_COORDINATES, ROOM_NOT_FOUND,
	EMPTY_LINE, START_END_MISSING, NO_START_ROOM, NO_END_ROOM, INVALID_LINK
}						t_type;

typedef struct			s_rm_list
{
	char				*name;
	int					x;
	int					y;
	int					h;
	struct s_rm_list	*next;
}						t_rm_list;

typedef struct			s_struct
{	
	char				isstart;
	char				wait_start;
	char				wait_end;
	char				isend;
	char				isants;
	int					ants;
	char				flag;
	char				only_links;

	t_rm_list			*start;
	t_rm_list			*end;
	t_rm_list			*rooms;
	t_rm_list			**table;
	t_type				e_errors;
	
}						t_info;

# define START "##start"
# define END "##end"
# define INITIALIZE (t_info){0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL}

int		check_line(t_info *info, char *str);
int		error_mng(t_info *info, int err_nb, char *s);
void	put_room_to_table(t_info *info, char **split);
t_rm_list	*room_lstnew(char **split);
void	room_lst_push_back(t_rm_list **begin_list, t_rm_list *new, t_info *info);
unsigned int	hash(char *str);
void	li_lst_push_back(t_list **begin_list, t_list *new);
void	room_add_lst(t_rm_list **begin, t_rm_list *new); //mybe do not need
int		room_check(t_info *info, char *str);
int		end_check(t_info *info);
int		start_check(t_info *info);
int		assign_start_end(t_info *info, char *str);
int		hashcheck(t_info *info, char *str);

#endif
