/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 19:34:39 by mshpakov          #+#    #+#             */
/*   Updated: 2018/12/21 19:34:41 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		free_map(char **str)
{
	int		i;

	if (!str)
		return ;
	i = 0;
	WHILE_DO(str[i], free(str[i++]));
	free(str);
}

int			ft_sqrt(int nb)
{
	int		root;

	root = 0;
	while (++root <= nb)
		RET_IF(root, root * root == nb);
	return (0);
}

void		clean_map(char **map, int side, char c)
{
	int		j;
	int		i;

	j = -1;
	while (++j < side)
	{
		i = -1;
		while (++i < side)
			IF_DO(map[j][i] == c, map[j][i] = EMPTY);
	}
}

void		clear_last(t_shape *start)
{
	t_shape	*shape;

	shape = start;
	while (shape)
	{
		LAST[0] = -1;
		LAST[1] = -1;
		shape = NEXT;
	}
}
