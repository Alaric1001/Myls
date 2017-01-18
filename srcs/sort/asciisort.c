/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asciisort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 09:21:56 by asenat            #+#    #+#             */
/*   Updated: 2017/01/18 09:57:49 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_list		**getmin(t_list **lst)
{
	t_list **ret;

	ret = lst;
	while (*lst)
	{
		if (ft_strcmp(((t_stat*)(*ret)->content)->fname,
					((t_stat*)(*lst)->content)->fname) > 0)
			ret = lst;
		lst = &(*lst)->next;
	}
	return (ret);
}

void		asciisort(t_list **lst)
{
	void	*tmp;
	t_list	**min;

	lst = &(*lst)->next;
	while (*lst)
	{
		min = getmin(lst);
		tmp = (*lst)->content;
		(*lst)->content = (*min)->content;
		(*min)->content = tmp;
		lst = &(*lst)->next;
	}
}
