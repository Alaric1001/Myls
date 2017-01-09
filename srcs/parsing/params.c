/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 09:15:57 by asenat            #+#    #+#             */
/*   Updated: 2017/01/06 12:50:09 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static char		*get_opt(char *opt, char *arg, char *optlst)
{
	char	 *tmp;
	int		i;

	tmp = arg;
	while (*tmp)
	{
		i = 0;
		while (optlst[i++])
			if (optlst[i - 1] == *tmp)
			{
				opt = ft_strcappend(opt, *tmp);
				break ;
			}
		if ((unsigned int)i - 1 == ft_strlen(optlst))
			exit(1); //invalid option -- 'x'
		++tmp;
	}
	return (opt);
}

char			**getoptions(int pcount, char **params, char **options)
{
	int i;

	i = 1;
	while (i < pcount && params[i][0] == '-')
			*options = get_opt(*options, params[i++] + 1, "laRtr");
	return (params + i);
}
