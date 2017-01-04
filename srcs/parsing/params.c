#include "ls.h"

static char		*get_c_sort(char *opt, char *arg)
{
	if (*arg != '=')
		exit(1); // option '--sort' requires an argument
	++arg;
	if (!ft_strcmp(arg, "time"))
		return (ft_strcappend(opt, 't'));
	else
		exit(1); // invalid argument 'x' for '--sort'
}

static char		*get_fullopt(char *opt, char *arg)
{
	if (!arg)
		return (opt);
	if (!ft_strncmp(arg, "sort", 4))
		return (get_c_sort(opt, arg + 4));
	else if (!ft_strcmp(arg, "reverse"))
		return (ft_strcappend(opt, 'r'));
	else if (!ft_strcmp(arg, "all"))
		return (ft_strcappend(opt, 'a'));
	else if (!ft_strcmp(arg, "recursive"))
		return (ft_strcappend(opt, 'R'));
	else
		exit(1); // unrecogniwed option '--x'
}

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
				opt = ft_strcappend(opt, *tmp);
		if ((unsigned int)i == ft_strlen(optlst))
			exit(1); //invalid option -- 'x'
		++tmp;
	}
	return (opt);
}

char			*getoptions(int pcount, char **params)
{
	char		*res;

	res = NULL;
	while (--pcount > 0)
	{
		if (params[pcount][0] != '-')
			continue;
		if (!params[pcount][1])
			continue;
		if (params[pcount][1] == '-')
			res = get_fullopt(res, params[pcount] + 2);
		else
			res = get_opt(res, params[pcount] + 1, "laRtr");
		
	}
	return (res);
}
