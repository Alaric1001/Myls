/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 17:12:38 by asenat            #+#    #+#             */
/*   Updated: 2017/01/09 12:54:33 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char	*path_append(char *path, char *app)
{
	char *ret;

	ret = ft_strdup(path);
	if (path[ft_strlen(path) - 1] != '/')
		ret = ft_strappend(ret, "/");
	ret = ft_strappend(ret, app);
	return (ret);
}

t_stat	*newstat(char *dname, int dtype, char *path)
{
	t_stat *ret;

	ret = (t_stat*)ft_memalloc(sizeof(struct s_stat));
	ret->fpath = path;
	ret->fname = dname;
	ret->ftype = dtype;
	return (ret);
}

t_list	*getdirs(char *path, t_list **lst)
{
	t_list	*ret;
	t_list	*removed;
	t_list	**tmp;
	char	*ctt;

	ret = ft_lstnew(0, 0);
	tmp = &ret;
	while(*lst)
	{
		ctt = ((t_stat*)(*lst)->content)->fname;
		if (((t_stat*)(*lst)->content)->ftype == DT_DIR &&
				(ft_strcmp(ctt, ".") && ft_strcmp(ctt, "..")))
		{
			ctt = path_append(path, ((t_stat*)(*lst)->content)->fname);
			(*tmp) = ft_lstnew(ctt, ft_strlen(ctt) + 1);
			tmp = &(*tmp)->next;
		}
		removed = (*lst)->next;
		ft_memdel(&((*lst)->content));
		ft_memdel((void**)&(*lst));
		*lst = removed;
	}
	return (ret);
}
