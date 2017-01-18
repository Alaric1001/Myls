/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 09:15:57 by asenat            #+#    #+#             */
/*   Updated: 2017/01/18 09:57:09 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static char		*get_opt(char *opt, char *arg, char *optlst)
{
	char	*tmp;
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
		{
			ft_putstr_fd("illegal option -- ", 2);
			ft_putchar_fd(*tmp, 2);
			ft_putstr_fd("\nusage: ./ft_ls [", 2);
			ft_putstr_fd(optlst, 2);
			ft_putendl_fd("] [file ...]", 2);
			exit(1);
		}
		++tmp;
	}
	return (opt);
}

char			**getoptions(int pcount, char **params, char **options)
{
	int i;

	i = 1;
	while (i < pcount && params[i][0] == '-' && params[i][1])
		*options = get_opt(*options, params[i++] + 1, "laRtrf");
	return (params + i);
}
