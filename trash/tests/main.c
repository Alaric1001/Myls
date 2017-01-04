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

void	stock(DIR *dir, t_tree *t, char *cur_dir, int i)
{
	struct dirent *curr;
	DIR *tmp;
	t_tree *new;
	char *new_path;
	t_content *ctt;

	curr = readdir(dir);
	if (!curr)
		return ;
	printf("%i > %s\n", i, curr->d_name);
	ctt = (t_content*) ft_memalloc(sizeof(struct s_content));
	new_path = path_append(cur_dir, curr->d_name);
	ctt->filename = new_path;
	t = ft_createtree(ctt);
	i++;
	if (curr->d_type == 4 && curr->d_name[0] != '.')
		if (tmp = opendir(new_path))
			stock(tmp, t->left, new_path, i);
	stock(dir, t->right, cur_dir, i);
}

void	stockv2(char *path, t_tree **stock)
{
	static struct dirent	*dirent;
	DIR						*dir;
	t_content				*ctt;
	t_tree					*tree;
	
	if(!(dir = opendir(path)))
		return ;
	tree = (*stock);
	printf("1> %p -", *stock);
	tree = tree->left;
	while ((dirent = readdir(dir)))
	{
		ctt = (t_content*) ft_memalloc(sizeof(struct s_content));
		ctt->filename = path_append(path, dirent->d_name);
		tree = ft_createtree(ctt);
		ft_putendl(ctt->filename);
//		if (dirent->d_type == DT_DIR && dirent->d_name[0] != '.')
//			stockv2(ctt->filename, &tree);
		tree = tree->right;
	}
	printf(" 2>%p\n", *stock);
	closedir(dir);
}

void oui(t_tree *t)
{
	if (t == NULL)
		return ;
	ft_putendl(((t_content*)t->value)->filename);
	oui(t->left);
	oui(t->right);
}

int		main(int ac, char **av)
{
	DIR *dir;
	struct dirent *yay;
	t_tree *tree;
	t_tree *s;
	t_content *ctt;

	dir = opendir(av[1]);
	ctt = (t_content*) ft_memalloc(sizeof(struct s_content));
	ctt->filename =av[1];
	tree = ft_createtree(ctt);
	stockv2(av[1], &tree);
	ft_putendl("hopla:");
	oui(tree);
	closedir(dir);
}
