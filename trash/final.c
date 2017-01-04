#include <dirent.h>
#include <stdio.h>
#include "libft/includes/libft.h"

typedef	struct	s_ctt
{
	char	*fname;
	int		ftype;
	t_list	*sub;
}				t_ctt;

t_ctt	*newctt(char *fname, int ftype)
{
	t_ctt	*ctt;

	ctt = (t_ctt*) ft_memalloc(sizeof(struct s_ctt));
	ctt->fname = fname;
	ctt->ftype = ftype;
	return (ctt);
}

char	*path_append(char *path, char *app)
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

void	stock(t_list **list, char *path)
{
	static struct dirent	*dirent;
	DIR						*dir;
	t_ctt					*ctt;
	t_list					*tmp;
	char					*npath;

	if (!(dir = opendir(path)))
		return ;
	list = &(*list)->next;
	while ((dirent = readdir(dir)))
	{
		ctt = newctt(dirent->d_name, dirent->d_type);
		*list = ft_lstnew(ctt, sizeof(struct s_ctt));
		ft_putendl(ctt->fname);
		if (dirent->d_type == DT_DIR && dirent->d_name[0] != '.')
		{
			ft_putendl("<<<< oui >>>");
			npath = path_append(path, dirent->d_name);
			ctt->sub = ft_lstnew(newctt(npath, 0), sizeof(struct s_ctt));
			stock(&(ctt->sub), npath);
		}
		list = &(*list)->next;
	}
	closedir(dir);
}

void	show(t_list *list)
{
	t_ctt	*ctt;

	while (list)
	{
		ctt = (t_ctt*)(list->content);
		ft_putendl(ctt->fname);
		if(ctt->ftype == DT_DIR)
		{
			show(ctt->sub);
		}
		list = list->next;
	}
	/* FREE */
}

void ihh(t_list *l)
{
	printf(">%i\n", *((int*)l->content));
}

int main(int ac, char **av)
{
	DIR *dir;
	t_list *list;
	t_ctt	*ctt;

	ctt = newctt(av[1], 0);
	list = ft_lstnew(ctt, sizeof(ctt));
	stock(&list, av[1]);
	ft_putendl("-------");
	show(list);
	return (0);
}
