/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_disp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 10:47:35 by asenat            #+#    #+#             */
/*   Updated: 2017/01/09 18:14:34 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <sys/stat.h>

void	display(t_list *lst, int padding, struct stat filestat)
{

}

void	advanced_disp(t_list  **lst)
{
	static size_t	padding = 0;
	int				tmp;
	int				total;
	t_list			*todisp;
	struct stat		filestat;

	todisp = *lst;
	(!(((t_stat*)todisp->content)->fpath)) ? padding = 0 : 0;
	if (!padding)
	{
		total = 0;
		while ((lst = &(*lst)->next))
		{
			stat(((t_stat*)(*lst)->content)->fpath, &filestat);
			if (filestat.st_size > padding)
				padding = ft_getnblen(filestat.st_size);
			total += filestat.st_size;
		}
		ft_queuestr("total ");
		ft_queuenbr(total);
		ft_queuechar('\n');
	}
	display(todisp, padding, filestat);
}
