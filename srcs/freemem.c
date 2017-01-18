/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freemem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 09:22:42 by asenat            #+#    #+#             */
/*   Updated: 2017/01/17 10:19:44 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	delstat(void *ctt, size_t size)
{
	t_stat *s;

	s = (t_stat*)ctt;
	ft_strdel(&s->fpath);
	ft_strdel(&s->fname);
	ft_memdel((void**)&s);
	(void)size;
}

void	delstr(void *ct, size_t s)
{
	ft_memdel(&ct);
	(void)s;
}

t_list	*freeandnext(t_list *l, void (*del)(void*, size_t))
{
	t_list *n;

	n = l->next;
	ft_lstdelone(&l, del);
	return (n);
}

t_list	*newlistandfree(t_stat *stat)
{
	t_list *r;

	r = ft_lstnew(stat, sizeof(struct s_stat));
	ft_memdel((void**)&stat);
	return (r);
}
