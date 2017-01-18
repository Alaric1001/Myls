/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_disp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 09:48:43 by asenat            #+#    #+#             */
/*   Updated: 2017/01/18 09:50:01 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <grp.h>
#include <uuid/uuid.h>
#include <sys/types.h>
#include <pwd.h>
#include <time.h>
#include <limits.h>

void	printtotal(size_t total)
{
	ft_queuestr("total ");
	ft_queuenbr(total);
	ft_queuechar('\n');
}

void	disp(t_list *lst, t_pad *padding)
{
	t_stat		*stat;

	stat = (t_stat*)lst->content;
	queueperms(stat->fstat.st_mode, '-');
	dispattr(stat->fpath);
	ft_queuechar(' ');
	padnb(padding->nlink_p, stat->fstat.st_nlink);
	ft_queuechar(' ');
	ft_queuestr(getpwuid(stat->fstat.st_uid)->pw_name);
	ft_queuechar('\t');
	padstr(padding->grgid_p, getgrgid(stat->fstat.st_gid)->gr_name);
	ft_queuestr("  ");
	dispsize(stat->fstat, padding);
	ft_queuechar(' ');
	disptime(stat->fstat.st_mtimespec);
	ft_queuechar(' ');
	printcolorname(stat->fname, stat->fstat.st_mode);
	displnk(stat->fstat.st_mode, stat->fpath);
	ft_queuechar('\n');
}

void	advanced_disp(t_list **lst)
{
	static t_pad	*padding = NULL;
	size_t			total;
	t_list			*todisp;
	struct stat		filestat;

	todisp = *lst;
	if (!padding)
	{
		padding = (t_pad*)ft_memalloc(sizeof(struct s_pad));
		total = 0;
		while (*lst)
		{
			filestat = ((t_stat*)(*lst)->content)->fstat;
			update_padding(filestat, padding);
			total += filestat.st_blocks;
			lst = &(*lst)->next;
		}
		(!(((t_stat*)todisp->content)->nototal)) ? printtotal(total) : 0;
	}
	disp(todisp, padding);
	(!todisp->next) ? ft_memdel((void**)&padding) : 0;
}
