/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 19:33:11 by mshpakov          #+#    #+#             */
/*   Updated: 2018/12/21 19:33:13 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void			all_same(t_shape *start, t_sq *sq)
{
	t_shape		*shape;

	shape = start;
	sq->count = T;
	WHILE_DO(T == sq->count && NEXT, shape = NEXT);
	SAME = !NEXT && T == sq->count ? sq->count : 0;
}

int				analyze_shapes(t_shape *start, t_sq *sq)
{
	t_shape		*shape;
	int			rt;
	int			lt;
	int			rb;
	int			lb;

	rt = 0;
	lt = 0;
	rb = 0;
	lb = 0;
	shape = start;
	all_same(shape, sq);
	while (shape)
	{
		if (T != 19)
			IF_DO(T == 6 || T == 11 || T == 13 || T == 14 || T > 16, rt++);
		IF_DO(T == 5 || T == 12 || (T > 14 && T != 18), lt++);
		IF_DO(T == 2 || T == 3 || T == 5 || T == 7 || T == 16 || T == 18, rb++);
		IF_DO(T == 3 || T == 4 || T == 6 || T == 8 || T == 14 || T == 19, lb++);
		shape = NEXT;
	}
	RET_IF(0, NB_SH == 1);
	RET_IF(1, ++rt >= NB_SH || ++lt >= NB_SH || ++rb >= NB_SH || ++lb >= NB_SH);
	return (0);
}

t_sq			*get_square(t_sq **sq, t_shape *start, char fill)
{
	int			area;
	t_shape		*shape;

	shape = start;
	RET_IF(NULL, !((*sq) = (t_sq *)malloc(sizeof(t_sq))));
	(*sq)->nb_shapes = (fill - 'A' + 1);
	area = (*sq)->nb_shapes * 4;
	area = area + analyze_shapes(shape, *sq);
	WHILE_DO(((*sq)->side = ft_sqrt(area)) == 0, area++);
	IF_DO((*sq)->same == 9 && (*sq)->side % 2 != 0, (*sq)->side++);
	return (*sq);
}

int				final(t_shape *start, char fill)
{
	t_sq		*sq;
	char		**map;
	int			j;

	j = -1;
	sq = get_square(&sq, start, fill);
	map = NULL;
	while (j != OK)
	{
		RET_IF(ERR, !(map = make_map(sq)));
		j = arrange(start, map, sq);
		BREAK_IF(j == OK);
		SIDE++;
		clear_last(start);
		free_map(map);
	}
	j = -1;
	WHILE_DO(map[++j], ft_putendl(map[j]));
	free_map(map);
	free(sq);
	return (OK);
}
