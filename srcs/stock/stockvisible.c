/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stockvisible.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 10:18:30 by asenat            #+#    #+#             */
/*   Updated: 2017/01/17 16:55:49 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		stockvisible(t_list **lst, struct dirent *drent, char *path)
{
	t_stat *stat;

	if (drent->d_name[0] == '.')
		return (0);
	stat = newstat(drent->d_name, path);
	*lst = ft_lstnew(stat, sizeof(struct s_stat));
	ft_memdel((void**)&stat);
	return (1);
}
