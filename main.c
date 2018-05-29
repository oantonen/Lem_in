/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 20:04:37 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/20 19:38:06 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlemin.h"

void	before_start(t_info *info, t_list **begin, char **argv)
{
	if (argv[1] && ft_strequ(argv[1], "-hh"))
		print_req(info);
	else if ((argv[1] && ft_strequ(argv[1], "-h")) || (!ft_strequ(argv[1], \
		"-hh") && !ft_strequ(argv[1], "-q") && !ft_strequ(argv[1], "-p") \
		&& !ft_strequ(argv[1], "-d")))
		print_usage(info);
	*info = INITIALIZE;
	info->argv = argv;
	info->e_errors = OK;
	info->rooms = NULL;
	*begin = NULL;
	info->table = (t_rm_list**)malloc(sizeof(t_rm_list*) * 524287);
	ft_memset(info->table, 0, 524287 * sizeof(t_rm_list*));
}

void	graph_and_co(t_info *info, t_rm_list **table, t_list *begin)
{
	t_pth	**pth;
	t_list	*ptr31;
	t_list	*ptr;

	bfs_path(info, info->table);
	if (info->path_q == 0)
		error_mng(info, NO_PATH, "");
	count_real_pathes(info, info->paths);
	pth = (t_pth**)malloc(sizeof(t_pth*) * (info->path_q));
	transform_paths(info, info->paths, pth, ptr31);
	if (!info->argv[1] || !ft_strequ(info->argv[1], "-q"))
		while (begin)
		{
			ft_printf("\e[38;5;158m%s\e[m\n", begin->content);
			free(begin->content);
			ptr = begin;
			begin = begin->next;
			free(ptr);
		}
	ft_putstr("\n");
	print_paths(info, pth, info->pth_len, info->path_q);
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
	t_list	*ptr;

	before_start(&info, &begin, argv);
	while (get_next_line(0, &first) > 0)
	{
		if (check_line(&info, first) == 1)
			li_lst_push_back(&begin, ft_lstnew(first, 0));
		else if (!check_line(&info, first) && !info.only_links)
			error_mng(&info, NOT_OK, "");
		else if (check_line(&info, first) == 0)
			break ;
	}
	if (info.only_links == 0)
		error_mng(&info, NOT_OK, "");
	graph_and_co(&info, info.table, begin);
	return (0);
}
