#ifndef LS_H
# define LS_H

#include "../libft/includes/libft.h"
#include <dirent.h>

typedef struct	s_stat
{
	char	*fname;
	int		ftype;
}				t_stat;

char			*getoptions(int pcount, char **params);
void			standard_way(char *path, char *options, int sevdir);

#endif
