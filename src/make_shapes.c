/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 13:02:05 by mshpakov          #+#    #+#             */
/*   Updated: 2018/12/18 13:02:06 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			get_type_zero(const int *t)
{
	RET_IF(0, t[1] != 1);
	if (t[2] == 0 && t[3] == 2)
	{
		RET_IF(1, t[4] == 0 && t[5] == 3);
		RET_IF(2, t[4] == 1 && t[5] == 0);
		RET_IF(3, t[4] == 1 && t[5] == 1);
		RET_IF(4, t[4] == 1 && t[5] == 2);
	}
	else if (t[2] == 1)
	{
		RET_IF(5, t[3] == -1 && t[4] == 1 && t[5] == 0);
		RET_IF(6, t[3] == 1 && t[4] == 1 && t[5] == 2);
		RET_IF(7, t[3] == 0 && t[4] == 2 && t[5] == 0);
		RET_IF(8, t[3] == 1 && t[4] == 2 && t[5] == 1);
		RET_IF(9, t[3] == 0 && t[4] == 1 && t[5] == 1);
	}
	return (0);
}

int			get_type_one(const int *t)
{
	if (t[1] == 0 && t[2] == 2)
	{
		RET_IF(10, t[3] == 0 && t[4] == 3 && t[5] == 0);
		RET_IF(13, t[3] == 0 && t[4] == 2 && t[5] == 1);
		RET_IF(15, t[3] == -1 && t[4] == 2 && t[5] == 0);
	}
	else if (t[2] == 1 && t[4] == 1)
	{
		RET_IF(11, t[1] == 0 && t[3] == 1 && t[5] == 2);
		RET_IF(12, t[1] == -2 && t[3] == -1 && t[5] == 0);
		RET_IF(17, t[1] == -1 && t[3] == 0 && t[5] == 1);
	}
	else if (t[2] == 1 && t[4] == 2)
	{
		RET_IF(14, t[1] == 0 && t[3] == 1 && t[5] == 1);
		RET_IF(16, t[1] == -1 && t[3] == 0 && t[5] == -1);
		RET_IF(18, t[1] == 0 && t[3] == 1 && t[5] == 0);
		RET_IF(19, t[1] == -1 && t[3] == 0 && t[5] == 0);
	}
	return (0);
}

int			shape_info(t_shape *shape)
{
	int		i;
	int		max_h;
	int		max_w;

	if (TAB[0] == 0)
		T = get_type_zero(TAB);
	else if (TAB[0] == 1)
		T = get_type_one(TAB);
	RET_IF(ERR, T == 0);
	i = -1;
	max_h = 0;
	max_w = 0;
	while (++i < 6)
	{
		if (i % 2 == 0 && TAB[i] > max_h)
			max_h = TAB[i];
		else if (i % 2 != 0 && TAB[i] > max_w)
			max_w = TAB[i];
	}
	H = max_h;
	W = max_w;
	return (OK);
}

int			shape_tab(char **a, t_shape *shape, int j, int i)
{
	int		x;
	int		y;
	int		no;

	x = -1;
	no = -2;
	while (++j < 4)
	{
		i = -1;
		while (++i < 4)
		{
			RET_IF(ERR, a[j][i] != FULL && a[j][i] != EMPTY);
			if (a[j][i] == FULL && x == -1 && (y = j) >= 0)
				x = i;
			else if (a[j][i] == FULL)
			{
				RET_IF(ERR, no > 2);
				TAB[(no += 2)] = j - y;
				TAB[no + 1] = i - x;
			}
		}
	}
	RET_IF(ERR, no != 4);
	RET_IF(ERR, shape_info(shape) == ERR);
	return (OK);
}

t_shape		*get_shape(t_shape **start, char fill)
{
	t_shape	*shape;
	t_shape	*current;

	current = *start;
	while (current)
	{
		BREAK_IF(!current->next);
		current = current->next;
	}
	RET_IF(NULL, !(shape = (t_shape *)malloc(sizeof(t_shape))));
	ft_bzero(TAB, sizeof(TAB));
	LAST[0] = -1;
	LAST[1] = -1;
	T = 0;
	FILL = fill;
	NEXT = NULL;
	PREV = NULL;
	if (!*start)
		*start = shape;
	else if (current)
	{
		current->next = shape;
		PREV = current;
	}
	return (shape);
}
