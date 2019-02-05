/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 19:38:53 by mshpakov          #+#    #+#             */
/*   Updated: 2018/12/21 19:38:55 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char		**fill_map(char **map, int side)
{
	int		i;
	int		j;

	j = -1;
	while (++j < side)
	{
		RET_IF(NULL, !(map[j] = (char *)malloc(sizeof(char) * (side + 1))));
		i = -1;
		WHILE_DO(++i < side, map[j][i] = '.');
		map[j][side] = '\0';
	}
	map[j] = NULL;
	return (map);
}

char		**make_map(t_sq *sq)
{
	char	**map;

	RET_IF(NULL, !(map = (char **)malloc(sizeof(char *) * (SIDE + 1))));
	RET_IF(NULL, !(map = fill_map(map, SIDE)));
	return (map);
}
