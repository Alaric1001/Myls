/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timesort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 15:06:18 by asenat            #+#    #+#             */
/*   Updated: 2017/01/18 09:57:52 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_list		**getmintime(t_list **lst)
{
	t_list **ret;

	ret = lst;
	while (*lst)
	{
		if (((t_stat*)(*ret)->content)->fstat.st_mtimespec.tv_sec <
				((t_stat*)(*lst)->content)->fstat.st_mtimespec.tv_sec)
			ret = lst;
		lst = &(*lst)->next;
	}
	return (ret);
}

void		timesort(t_list **lst)
{
	void	*tmp;
	t_list	**min;

	lst = &(*lst)->next;
	while (*lst)
	{
		min = getmintime(lst);
		tmp = (*lst)->content;
		(*lst)->content = (*min)->content;
		(*min)->content = tmp;
		lst = &(*lst)->next;
	}
}
