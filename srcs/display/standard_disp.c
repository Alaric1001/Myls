/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard_disp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 09:52:57 by asenat            #+#    #+#             */
/*   Updated: 2017/01/09 17:11:28 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	standard_disp(t_list **list)
{
	ft_queuestr(((t_stat*)(*list)->content)->fname);
	if ((*list)->next)
		ft_queuestr("  ");
	else
		ft_queuestr("\n");
}
