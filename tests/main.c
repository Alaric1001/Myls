/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 12:51:24 by asenat            #+#    #+#             */
/*   Updated: 2016/12/20 17:51:57 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "../libft/includes/libft.h"
#include "../libft/includes/ft_tree.h"

typedef struct	s_content {
	char *filename;
}				t_content;

void	show(DIR *dir, int sub, char *dname)
{
	struct dirent *yay;
	static char *arrow  = "----------";
	static char path;
	DIR *tmp;
	char	*newpath;

	yay = readdir(dir);
	if (yay == NULL)
		return ;
	printf("%.*s> {%s%s}\n", sub, arrow, dname, yay->d_name);
	if (yay->d_type == 4 && strcmp(yay->d_name, ".") && strcmp(yay->d_name, ".."))
	{
		newpath = ft_strnew(ft_strlen(dname) + ft_strlen(yay->d_name) + 1);
		ft_strcat(newpath, dname);
		ft_strcat(newpath, "/");
		ft_strcat(newpath, yay->d_name);
		tmp = opendir(newpath);
		show(tmp, sub + 1, newpath);
		ft_strdel(&newpath);
	}
	show(dir, sub, dname);
}

char *path_append(char *path, char *app)
{
	char *ap;
	char *tmp;

	ap = ft_strdup(app);
	if (path[ft_strlen(path) - 1] != '/')
	{
		tmp = ap;
		ap = ft_strjoin("/", ap);
		ft_strdel(&tmp);
	}
	ap = ft_realloc(ap, 1);
	ft_strcat(ap, "/");
	tmp = ft_strjoin(path, ap);
	ft_strdel(&ap);
	return (tmp);
}

void	stock(DIR *dir, t_tree *t, char *cur_dir)
{
	struct dirent *curr;
	DIR *tmp;
	t_tree *new;
	char *new_path;
	t_content *ctt;

	curr = readdir(dir);
	if (!curr)
		return ;
	ctt = (t_content*) ft_memalloc(sizeof(struct s_content));
	new_path = path_append(cur_dir, curr->d_name);
	ctt->filename = new_path;
	ft_putendl(ctt->filename);
	t->right = ft_createtree(ctt);
	ft_putendl("cousrdtdtddcous");
	if (!(curr->d_type == 4 && strcmp(curr->d_name, ".") && strcmp(curr->d_name, "..")))
		stock(dir, (t->right)->right, cur_dir);
	if(!(tmp = opendir(new_path)))
		return ;
	stock(tmp, (t->right)->left, new_path);
}

int		main(int ac, char **av)
{
	DIR *dir;
	struct dirent *yay;

	dir = opendir(av[1]);
	/*while ((yay = readdir(dir)))
		printf("->%s\n : %lld\n", yay->d_name, (long long)yay->d_ino);*/
	stock(dir, ft_createtree(av[1]), ft_strdup(av[1]));
	closedir(dir);
}
