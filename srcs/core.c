/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 16:59:09 by asenat            #+#    #+#             */
/*   Updated: 2017/01/18 09:55:44 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	writetitle(char *path)
{
	ft_queuestr(path);
	ft_queuestr(":\n");
}

int		readpath(t_list **lst, char *path, int (*stock)(t_list**,
			struct dirent*, char *path), int rec)
{
	static struct dirent	*dirent;
	DIR						*dir;
	char					*npath;

	if (!(dir = opendir(path)))
	{
		if (rec)
		{
			ft_writequeue();
			perror(path);
		}
		return (0);
	}
	lst = &(*lst)->next;
	while ((dirent = readdir(dir)))
	{
		if (stock(lst, dirent, (npath = path_append(path, dirent->d_name))))
			lst = &(*lst)->next;
		ft_strdel(&npath);
	}
	closedir(dir);
	return (1);
}

t_list	*standard_way(char *path, t_set set, int rec)
{
	t_list	*list;
	t_list	*tmp;
	int		ret;

	list = newlistandfree(newstat(0, 0));
	if (set.writetitle)
		writetitle(path);
	if (!(ret = readpath(&list, path, set.stock, rec)))
	{
		ft_lstdelone(&list, delstat);
		return (NULL);
	}
	if (set.sort)
		set.sort(&list);
	if (set.rev)
		ft_lstrev(&(list->next));
	tmp = list;
	while ((tmp = tmp->next))
		set.disp(&tmp);
	return (list);
}

void	recursive_way(char *path, t_set set)
{
	t_list	*l;
	t_list	*dir;
	char	*npath;

	if ((!(l = standard_way(path, set, 1))))
		return ;
	dir = getdirs(path, &l);
	while ((dir))
	{
		if ((npath = (char*)(dir->content)))
		{
			ft_queuechar('\n');
			set.writetitle = 1;
			recursive_way(npath, set);
		}
		dir = freeandnext(dir, delstr);
	}
}

void	start_process(char *path, t_set set, int multargs, t_list *files)
{
	t_list	*tmp;

	set.writetitle = multargs;
	tmp = NULL;
	if (!path)
	{
		if (set.sort)
			set.sort(&files);
		if (set.rev)
			ft_lstrev(&(files->next));
		tmp = files;
		while ((tmp = freeandnext(tmp, delstat)))
			set.disp(&tmp);
		tmp = NULL;
	}
	else if (set.recursive)
		recursive_way(path, set);
	else
		tmp = standard_way(path, set, 0);
	(tmp) ? ft_lstdel(&tmp, delstat) : 0;
}
