/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 17:12:38 by asenat            #+#    #+#             */
/*   Updated: 2017/01/18 11:33:37 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "../libft/includes/ft_colors.h"

char	*path_append(char *path, char *app)
{
	char *ret;

	ret = ft_strdup(path);
	if (path[ft_strlen(path) - 1] != '/')
		ret = ft_strappend(ret, "/");
	ret = ft_strappend(ret, app);
	return (ret);
}

t_stat	*newstat(char *dname, char *path)
{
	t_stat		*ret;
	struct stat	st;

	ret = (t_stat*)ft_memalloc(sizeof(struct s_stat));
	lstat(path, &st);
	ret->fpath = ft_strdup(path);
	ret->fname = ft_strdup(dname);
	ret->fstat = st;
	ret->nototal = 0;
	return (ret);
}

t_list	*getdirs(char *path, t_list **lst)
{
	t_list	*ret;
	t_list	**tmp;
	char	*del;
	t_stat	*s;

	ret = ft_lstnew(0, 0);
	tmp = &ret->next;
	while ((*lst = freeandnext(*lst, delstat)))
	{
		s = ((t_stat*)(*lst)->content);
		if ((S_ISDIR(s->fstat.st_mode) && (ft_strcmp(s->fname, ".")
						&& ft_strcmp(s->fname, ".."))))
		{
			del = s->fname;
			s->fname = path_append(path, s->fname);
			ft_strdel(&del);
			(*tmp) = ft_lstnew(s->fname, ft_strlen(s->fname) + 1);
			tmp = &(*tmp)->next;
		}
	}
	return (freeandnext(ret, delstr));
}

void	printcolorname(char *fname, mode_t m)
{
	if (S_ISDIR(m) && (m & S_IWOTH) && (m & S_ISVTX))
		ft_queuestr(HGREEN);
	if (S_ISDIR(m) && (m & S_IWOTH) && !(m & S_ISVTX))
		ft_queuestr(HYELLOW);
	if (S_ISDIR(m) && !(m & S_IWOTH) && !(m & S_ISVTX))
		ft_queuestr(BLUE);
	if (S_ISREG(m) && (m & S_IXUSR) && (m & S_ISUID))
		ft_queuestr(HRED);
	if (S_ISREG(m) && (m & S_IXUSR) && (m & S_ISGID))
		ft_queuestr(HYELLOW);
	if (S_ISREG(m) && (m & S_IXUSR) &&
			!(m & S_ISGID) && !(m & S_ISUID))
		ft_queuestr(RED);
	S_ISBLK(m) ? ft_queuestr(HCYAN) : 0;
	S_ISCHR(m) ? ft_queuestr(HYELLOW) : 0;
	S_ISLNK(m) ? ft_queuestr(PURPLE) : 0;
	S_ISFIFO(m) ? ft_queuestr(YELLOW) : 0;
	S_ISSOCK(m) ? ft_queuestr(GREEN) : 0;
	(S_ISBLK(m) || S_ISCHR(m)) ? ft_queuestr(BLUE) : 0;
	ft_queuestr(fname);
	ft_queuestr(RESET);
}
