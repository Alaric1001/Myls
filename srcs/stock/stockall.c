/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stockall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 10:48:43 by asenat            #+#    #+#             */
/*   Updated: 2017/01/17 15:22:52 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		stockall(t_list **lst, struct dirent *drent, char *path)
{
	t_stat *stat;

	stat = newstat(drent->d_name, path);
	*lst = ft_lstnew(stat, sizeof(struct s_stat));
	ft_memdel((void**)&stat);
	return (1);
}
