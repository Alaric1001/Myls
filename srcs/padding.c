/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 17:17:39 by asenat            #+#    #+#             */
/*   Updated: 2017/01/18 09:56:19 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <grp.h>
#include <uuid/uuid.h>
#include <sys/types.h>
#include <pwd.h>

void	padnb(int pad, unsigned int size)
{
	int goal;
	int i;

	goal = pad - ft_getnblen(size);
	i = 0;
	while (i++ < goal)
		ft_queuechar(' ');
	ft_queuenbr(size);
}

void	padstr(int pad, char *grp)
{
	int i;

	pad = pad - ft_strlen(grp);
	i = 0;
	ft_queuestr(grp);
	while (i++ < pad)
		ft_queuechar(' ');
}

void	update_padding(struct stat stat, t_pad *pad)
{
	int slen;
	int glen;
	int	nlnlen;

	slen = ft_getnblen(stat.st_size);
	nlnlen = ft_getnblen(stat.st_nlink);
	glen = ft_strlen(getgrgid(stat.st_gid)->gr_name);
	(slen > pad->size_p) ? pad->size_p = slen : 0;
	(glen > pad->grgid_p) ? pad->grgid_p = glen : 0;
	(nlnlen > pad->nlink_p) ? pad->nlink_p = nlnlen : 0;
	((stat.st_rdev)) ? pad->isrdev = 1 : 0;
}
