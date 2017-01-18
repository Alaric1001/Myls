/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 08:55:50 by asenat            #+#    #+#             */
/*   Updated: 2017/01/17 18:34:48 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char	**checkav(char **av, t_list **l, int *len)
{
	int		i;
	DIR		*tmp;

	i = -1;
	while (av[++i])
	{
		if ((tmp = opendir(av[i])))
			closedir(tmp);
		else if (errno == ENOTDIR)
		{
			l = &(*l)->next;
			*l = newlistandfree(newstat(av[i], av[i]));
			((t_stat*)(*l)->content)->nototal = 1;
			av[i][0] = '\0';
		}
		else
		{
			perror(av[i]);
			av[i][0] = '\0';
		}
		++(*len);
	}
	return (av);
}

void	ls(char **av, int avlen, t_set set)
{
	int mltarg;

	mltarg = 0;
	while (avlen--)
	{
		if (!(**av))
		{
			av++;
			mltarg = 1;
			continue ;
		}
		(*(av + 1)) ? ++mltarg : 0;
		(!*(av + 1) && **av) ? ft_queuechar('\n') : 0;
		start_process(*av++, set, mltarg, NULL);
	}
}

t_set	fillset(char *options)
{
	t_set set;

	set.rev = (CONTAINS('r')) ? 1 : 0;
	set.stock = (CONTAINS('a') || CONTAINS('f')) ? &stockall : &stockvisible;
	set.disp = (CONTAINS('l')) ? &advanced_disp : &standard_disp;
	set.sort = (CONTAINS('t')) ? &timesort : &asciisort;
	if (CONTAINS('f'))
	{
		set.sort = NULL;
		set.rev = 0;
	}
	set.recursive = (CONTAINS('R')) ? 1 : 0;
	ft_strdel(&options);
	return (set);
}

int		main(int ac, char **av)
{
	char	*opt;
	t_set	set;
	int		avlen;
	t_list	*f;

	avlen = 0;
	av = getoptions(ac, av, &opt);
	set = fillset(opt);
	if (!(*av))
		start_process(".", set, 0, NULL);
	else
	{
		f = newlistandfree(newstat(0, 0));
		av = checkav(av, &f, &avlen);
		if (f->next)
			start_process(0, set, 0, f);
		else
			ft_lstdelone(&f, delstat);
		ls(av, avlen, set);
	}
	ft_writequeue();
	return (0);
}
