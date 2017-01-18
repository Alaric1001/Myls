/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_disputils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 13:36:05 by asenat            #+#    #+#             */
/*   Updated: 2017/01/18 09:58:22 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <sys/types.h>
#include <time.h>
#include <limits.h>
#include <sys/xattr.h>
#include <sys/acl.h>

void	queueperms(mode_t mode, char c)
{
	S_ISBLK(mode) ? c = 'b' : 0;
	S_ISCHR(mode) ? c = 'c' : 0;
	S_ISDIR(mode) ? c = 'd' : 0;
	S_ISFIFO(mode) ? c = 'p' : 0;
	S_ISLNK(mode) ? c = 'l' : 0;
	S_ISSOCK(mode) ? c = 's' : 0;
	ft_queuechar(c);
	ft_queuechar((mode & S_IRUSR) ? 'r' : '-');
	ft_queuechar((mode & S_IWUSR) ? 'w' : '-');
	c = (mode & S_IXUSR) ? 'x' : '-';
	((c == '-') && (mode & S_ISUID)) ? c = 'S' : 0;
	((c == 'x') && (mode & S_ISUID)) ? c = 's' : 0;
	ft_queuechar(c);
	ft_queuechar((mode & S_IRGRP) ? 'r' : '-');
	ft_queuechar((mode & S_IWGRP) ? 'w' : '-');
	c = (mode & S_IXGRP) ? 'x' : '-';
	((c == '-') && (mode & S_ISGID)) ? c = 'S' : 0;
	((c == 'x') && (mode & S_ISGID)) ? c = 's' : 0;
	ft_queuechar(c);
	ft_queuechar((mode & S_IROTH) ? 'r' : '-');
	ft_queuechar((mode & S_IWOTH) ? 'w' : '-');
	c = (mode & S_IXOTH) ? 'x' : '-';
	((c == '-') && (mode & S_ISVTX)) ? c = 'T' : 0;
	((c == 'x') && (mode & S_ISVTX)) ? c = 't' : 0;
	ft_queuechar(c);
}

void	disptime(struct timespec timespc)
{
	time_t	ct;
	char	*sub;
	char	*year;
	char	*full;

	ct = time(&ct);
	full = ctime(&(timespc.tv_sec));
	if (ct - timespc.tv_sec > TIME_LIM || ct - timespc.tv_sec < -TIME_LIM)
	{
		sub = ft_strsub(full, 4, 7);
		ft_queuestr(sub);
		year = ft_strsub(full, 20, 4);
		ft_queuechar(' ');
		ft_queuestr(year);
		ft_strdel(&year);
	}
	else
	{
		sub = ft_strsub(full, 4, 12);
		ft_queuestr(sub);
	}
	ft_strdel(&sub);
}

void	displnk(mode_t mode, char *path)
{
	char buf[PATH_MAX];

	if (!S_ISLNK(mode))
		return ;
	ft_bzero(buf, PATH_MAX);
	readlink(path, buf, PATH_MAX);
	ft_queuestr(" -> ");
	ft_queuestr(buf);
}

void	dispsize(struct stat st, t_pad *pad)
{
	int suppad;

	if (!(st.st_rdev))
	{
		suppad = (pad->isrdev) ? 7 : 0;
		padnb(pad->size_p + suppad, st.st_size);
	}
	else
	{
		padnb(2, major(st.st_rdev));
		ft_queuestr(", ");
		padnb(2, minor(st.st_rdev));
	}
}

void	dispattr(char *path)
{
	int		attr;
	acl_t	acl;

	attr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	if (attr > 0)
		ft_queuechar('@');
	else if (acl != NULL)
		ft_queuechar('+');
	else
		ft_queuechar(' ');
	acl_free((void*)acl);
}
