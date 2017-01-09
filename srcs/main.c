/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 08:55:50 by asenat            #+#    #+#             */
/*   Updated: 2017/01/09 17:14:52 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		main(int ac, char **av)
{
	char	*opt;
	int		mltarg;

	mltarg = 0;
	av = getoptions(ac, av, &opt);
	while (*av)
	{
		if(*(av + 1))
			++mltarg;
		start_process(*av++, opt, mltarg);
		ft_queuestr("\n");
	}
	ft_writequeue();
	return (0);
}
