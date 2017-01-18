/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 08:44:25 by asenat            #+#    #+#             */
/*   Updated: 2017/01/18 09:39:40 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <stdio.h>
# include <errno.h>
# include <sys/stat.h>

# define TIME_LIM 15552000
# define CONTAINS(c) ft_strchr(options, c)

typedef struct	s_stat
{
	char		*fpath;
	char		*fname;
	struct stat	fstat;
	int			nototal;
}				t_stat;

typedef struct	s_set
{
	int		(*stock)(t_list**, struct dirent*, char *path);
	void	(*disp)(t_list**);
	void	(*sort)(t_list**);
	int		writetitle;
	int		recursive;
	int		rev;
}				t_set;

typedef struct	s_pad
{
	int		size_p;
	int		grgid_p;
	int		nlink_p;
	int		isrdev;
}				t_pad;

char			**getoptions(int pcount, char **params, char **options);
void			start_process(char *path, t_set set, int multargs,
						t_list *files);

int				stockall(t_list **lst, struct dirent *drent, char *path);
int				stockvisible(t_list **lst, struct dirent *drent, char *path);

void			standard_disp(t_list **list);
void			advanced_disp(t_list **list);

void			padnb(int pad, unsigned int size);
void			padstr(int pad, char *grp);

void			asciisort(t_list **lst);
void			timesort(t_list **lst);

t_stat			*newstat(char *dname, char *path);
char			*path_append(char *path, char *app);
t_list			*getdirs(char *path, t_list **lst);
void			update_padding(struct stat stat, t_pad *pad);
void			printcolorname(char *fname, mode_t m);
void			queueperms(mode_t mode, char c);
void			disptime(struct timespec timespc);
void			displnk(mode_t mode, char *path);
void			dispsize(struct stat st, t_pad *pad);
void			dispattr(char *path);

void			delstat(void *ctt, size_t size);
void			delstr(void *ctt, size_t size);
t_list			*freeandnext(t_list *l, void (*del)(void*, size_t));
t_list			*newlistandfree(t_stat *stat);
#endif
