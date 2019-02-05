/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrange.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 19:41:49 by mshpakov          #+#    #+#             */
/*   Updated: 2018/12/21 19:41:51 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void			flood_fill(char **t, t_sq *sq, int j, int i)
{
	t[j][i] = '+';
	sq->count++;
	IF_DO(i <= SIDE - 1 && t[j][i + 1] == EMPTY, flood_fill(t, sq, j, i + 1));
	IF_DO(j < SIDE - 1 && t[j + 1][i] == EMPTY, flood_fill(t, sq, j + 1, i));
	IF_DO(i > 0 && t[j][i - 1] == EMPTY, flood_fill(t, sq, j, i - 1));
	IF_DO(j > 0 && t[j - 1][i] == EMPTY, flood_fill(t, sq, j - 1, i));
}

int				empty_check(char **map, t_sq *sq, t_shape *shape)
{
	int			empty;
	int			need;
	int			j;
	int			i;

	j = -1;
	empty = SIDE * SIDE - (FILL - 'A') * 4;
	need = (NB_SH - (FILL - 'A')) * 4;
	while (++j < SIDE)
	{
		i = -1;
		while (++i < SIDE)
		{
			if (map[j][i] == EMPTY)
			{
				sq->count = 0;
				flood_fill(map, sq, j, i);
				IF_DO(sq->count < 4, empty = empty - sq->count);
				RET_IF(ERR, empty < need);
			}
		}
	}
	return (OK);
}

int				place(t_shape *shape, char **map, t_sq *sq)
{
	int			no;
	int			check;

	no = 0;
	while (no < 5)
	{
		RET_IF(ERR, (sq->j + TAB[no]) < 0 || (sq->j + TAB[no]) >= SIDE);
		no++;
		RET_IF(ERR, (sq->i + TAB[no]) < 0 || (sq->i + TAB[no]) >= SIDE);
		no++;
		RET_IF(ERR, (map[sq->j + TAB[no - 2]][sq->i + TAB[no - 1]]) != EMPTY);
	}
	no = -2;
	map[sq->j][sq->i] = FILL;
	while ((no = no + 2) < 5)
		map[sq->j + TAB[no]][sq->i + TAB[no + 1]] = FILL;
	LAST[0] = sq->j;
	LAST[1] = sq->i;
	check = empty_check(map, sq, shape);
	clean_map(map, SIDE, '+');
	RET_IF(OK, check == OK);
	clean_map(map, SIDE, FILL);
	return (ERR);
}

int				arrange(t_shape *shape, char **map, t_sq *sq)
{
	int			done;

	while (FILL - 'A' < NB_SH)
	{
		sq->j = LAST[0];
		IF_DO(sq->j != -1, sq->j--);
		done = 0;
		while (++sq->j < SIDE - H && done != OK)
		{
			sq->i = sq->j == LAST[0] ? LAST[1] : -1;
			while (++sq->i < SIDE - W && done != OK)
			{
				IF_DO(map[sq->j][sq->i] == EMPTY, done = place(shape, map, sq));
				RET_IF(OK, done == OK && !NEXT);
			}
		}
		RET_IF(ERR, done != OK && (!PREV || SAME > 0));
		CONT_IF(done == OK && (shape = NEXT));
		LAST[0] = -1;
		LAST[1] = -1;
		shape = PREV;
		clean_map(map, SIDE, FILL);
	}
	return (ERR);
}
