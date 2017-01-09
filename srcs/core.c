/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 16:59:09 by asenat            #+#    #+#             */
/*   Updated: 2017/01/09 17:15:14 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	writetitle(char *path)
{
	ft_queuestr(path);
	ft_queuestr(":\n");
}

int		readpath(t_list **lst, char *path, int (*stock)(t_list**,
			struct dirent*, char *path))
{
	static struct dirent	*dirent;
	DIR						*dir;

	if (!(dir = opendir(path)))
	{
		if (errno == ENOTDIR) //TODO
			return (2);
		else
			perror(path);
		return (0);
	}
	lst = &(*lst)->next;
	while ((dirent = readdir(dir)))
		if(stock(&(*lst), dirent, path))
			lst = &(*lst)->next;
	closedir(dir);
	return (1);
}

t_list	*standard_way(char *path, t_set *set)
{
	t_list	*list;
	t_list	*tmp;
	int		ret;

	list = ft_lstnew(newstat(path, 0, 0), sizeof(struct s_stat));
	if (!(ret = readpath(&list, path, set->stock)))
		return (NULL);
	if (set->sort)
		set->sort(&list);
	if (set->rev)
		ft_lstrev(&(list->next));
	tmp = list;
	while ((tmp = tmp->next))
		set->disp(&tmp);
	return (list);
}

void	recursive_way(char *path, t_set *set)
{
	t_list	*l;
	t_list	*dir;
	t_list	*tmp;
	char	*npath;

	if((!(l = standard_way(path, set))))
		return ;
	dir = getdirs(path, &l);
	while (dir)
	{
		if ((npath = (char*)(dir->content)))
		{
			writetitle(npath);
			recursive_way(npath, set);
		}
		ft_strdel(&npath);
		tmp = dir->next;
		ft_memdel((void**)&dir);
		dir = tmp;
	}
}

void	start_process(char *path, char *options, int multargs)
{
	t_set *set;

	set = (t_set*)ft_memalloc(sizeof(struct s_set));
	set->rev = (ft_strchr(options, 'r')) ? 1 : 0;
	if (ft_strchr(options, 'a'))
		set->stock = &stockall;
	else
		set->stock = &stockvisible;
	if (ft_strchr(options, 'l'))
		set->disp = &advanced_disp;
	else
		set->disp = &standard_disp;
	if (multargs)
		writetitle(path);
	if (ft_strchr(options, 'R'))
		recursive_way(path, set);
	else
		standard_way(path, set); //TODO DEL
}
