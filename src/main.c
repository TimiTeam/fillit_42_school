/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 13:01:54 by mshpakov          #+#    #+#             */
/*   Updated: 2018/12/18 13:01:57 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		end(int c)
{
	IF_DO(c == 0, write(1, "error\n", 6));
	IF_DO(c == 1, write(1, "usage: ./fillit file_name\n", 26));
	return (1);
}

int		main(int ac, char **av)
{
	char	**s;
	t_shape	*st;
	t_shape	*tmp;
	t_read	*r;

	r = (t_read *)malloc(sizeof(t_read));
	r->ret = 21;
	r->fill = 'A';
	st = NULL;
	RET_IF(0, (ac != 2 || (r->fd = open(av[1], O_RDONLY)) == -1) && end(1));
	RET_IF(ERR, (r->fd == -1 || !(tmp = get_shape(&st, r->fill))) && end(0));
	while (r->ret == 21)
	{
		RET_IF(ERR, (r->ret = read(r->fd, r->buf, BUFF_SIZE)) < 20 && end(0));
		RET_IF(ERR, (r->ret == 21 && r->buf[20] != '\n') && end(0));
		RET_IF(ERR, r->buf[19] != '\n' && end(0));
		s = ft_strsplit(r->buf, '\n');
		RET_IF(ERR, shape_tab(s, tmp, -1, -1) == ERR && end(0));
		free_map(s);
		IF_DO(r->ret == 21, tmp = get_shape(&st, ++r->fill));
		RET_IF(ERR, tmp->fill > 'Z' && end(0));
	}
	final(st, r->fill);
	close(r->fd);
	return (0);
}
