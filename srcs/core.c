#include "ls.h"

int		test_stock(t_list **l, struct dirent *drent)
{
	t_stat *ctt;

	if (drent->d_name[0] == '.')
		return (0);
	ctt = (t_stat*)ft_memalloc(sizeof(struct s_stat));
	ctt->fname = drent->d_name;
	ctt->ftype = drent->d_type;
	*l = ft_lstnew(ctt, sizeof(struct s_stat));
	return (1);
}

void	show(t_list *t)
{
	t_stat *s;

	while (t)
	{
		s = (t_stat*)t->content;
		ft_putstr(s->fname);
		ft_putstr("  ");
		t = t->next;
	}
}


void	readpath(t_list **lst, char *path, int (*stock)(t_list**, struct dirent*))
{
	static struct dirent	*dirent;
	DIR						*dir;

	if (!(dir = opendir(path)))
		return ;
	lst = &(*lst)->next;
	while ((dirent = readdir(dir)))
		if(stock(&(*lst), dirent))
			lst = &(*lst)->next;
	closedir(dir);
}

void	standard_way(char *path, char *options, int sevdir)
{
	t_list *l;
	t_stat *s;

	s = (t_stat*)ft_memalloc(sizeof(struct s_stat));
	s->fname = path;
	l = ft_lstnew(s, sizeof(struct s_stat));
	readpath(&l, path, &test_stock);
	show(l);
}
