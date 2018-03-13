/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hlemin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 11:57:13 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/13 20:43:50 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HLEMIN_H
# define HLEMIN_H

# include "hprintf.h"
#include <stdio.h> ////
# include <stdbool.h>

typedef enum			e_type
{
	OK, DOUBLE_START, DOUBLE_END, NOT_OK, INVALID_ANTS, WRONG_ROOM_PROPERTIES, 
	ANT_IS_MISSING, DUPLICATED_ROOM, DUPLICATED_COORDINATES, ROOM_NOT_FOUND,
	EMPTY_LINE, START_END_MISSING, NO_START_ROOM, NO_END_ROOM, INVALID_LINK,
	NO_PATH

}						t_type;

typedef struct 			s_data
{
	char				*name;
	int					x;
	int					y;
	int					h;
	int					level;
	t_list				*link;
}						t_data;

typedef struct			s_rm_list
{
	t_data				*d;
	struct s_rm_list	*next;
	struct s_rm_list	*same_h;
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
	t_rm_list			*r1;
	t_rm_list			*r2;
	t_rm_list			*rooms;
	t_rm_list			**table;
	t_type				e_errors;
	
}						t_info;

# define START "##start"
# define END "##end"
# define INITIALIZE (t_info){0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL}

int		check_line(t_info *info, char *str);
bool		error_mng(t_info *info, int err_nb, char *s);
t_rm_list	*room_lstnew(t_data *data);
void	room_lst_push_back(t_rm_list **begin_list, t_rm_list *new, t_info *info);
unsigned int	hash(char *str);
void	li_lst_push_back(t_list **begin_list, t_list *new);
void	room_add_lst(t_rm_list **begin, t_rm_list *new); //mybe do not need
bool	room_check(t_info *info, char *str);
bool	end_check(t_info *info);
bool	start_check(t_info *info);
bool	assign_start_end(t_info *info, char *str);
bool	hashcheck(t_info *info, char *str);
void	put_room_to_table(t_rm_list **table, t_rm_list *new);
t_data	*create_data(char **split);
void	bfs_path(t_info *info, t_rm_list **table);


#endif
