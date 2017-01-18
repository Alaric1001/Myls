/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard_disp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 09:52:57 by asenat            #+#    #+#             */
/*   Updated: 2017/01/18 09:48:15 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	dopad(int col, int pad, char *fname, int end)
{
	int i;

	i = pad - ft_strlen(fname) + 1;
	if (col == 3 || end)
		ft_queuechar('\n');
	else
		while (i--)
			ft_queuechar(' ');
}

void	standard_disp(t_list **list)
{
	static size_t	pad = 0;
	static int		col = 1;
	t_stat			*stat;
	t_list			*todisp;

	todisp = *list;
	if (!pad)
	{
		while (*list)
		{
			stat = (t_stat*)(*list)->content;
			if (ft_strlen(stat->fname) > pad)
				pad = ft_strlen(stat->fname);
			list = &(*list)->next;
		}
	}
	stat = ((t_stat*)todisp->content);
	printcolorname(stat->fname, stat->fstat.st_mode);
	dopad(col, pad, stat->fname, !todisp->next);
	(!todisp->next) ? pad = 0 : 0;
	(col == 3 || !todisp->next) ? col = 1 : ++col;
}
