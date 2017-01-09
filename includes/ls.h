/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 08:44:25 by asenat            #+#    #+#             */
/*   Updated: 2017/01/09 12:53:21 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

#include "../libft/includes/libft.h"
#include <dirent.h>
#include <stdio.h>
#include <errno.h>

typedef struct	s_stat
{
	char	*fpath;
	char	*fname;
	int		ftype;
}				t_stat;

typedef struct	s_set
{
	int		(*stock)(t_list**, struct dirent*, char *path);
	void	(*disp)(t_list**);
	void	(*sort)(t_list**);
	int		rev;
}				t_set;

char			**getoptions(int pcount, char **params, char **options);
void			start_process(char *path, char *options, int multargs);

int				stockall(t_list **lst, struct dirent *drent, char *path);
int				stockvisible(t_list **lst, struct dirent *drent, char *path);

void			standard_disp(t_list **list);
void			advanced_disp(t_list **list);

t_stat			*newstat(char *dname, int dtype, char *path);
char			*path_append(char *path, char *app);
t_list			*getdirs(char *path, t_list **lst);
#endif
