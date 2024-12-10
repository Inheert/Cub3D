/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:44:11 by tclaereb          #+#    #+#             */
/*   Updated: 2024/12/10 09:20:26 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	t_map_display(t_map **tmap)
{
	t_map	*map;
	t_map	*tmp;

	map = *tmap;
	while (map)
	{
		tmp = map;
		while (tmp)
		{
			printf("%c", tmp->slot);
			tmp = tmp->right;
		}
		map = map->down;
		printf("\n");
	}
}

t_map_build	t_map_get_symbol(char c)
{
	if (c >= 48 && c <= 51)
		return (c - 48);
	if (c == 'P')
		return (PLAYER);
	return (-1);
}

t_map	*t_map_fill_line(char **old_map, t_map **map, int line)
{
	int	i;

	i = -1;
	while (old_map[line][++i])
	{
		map[line][i].slot = old_map[line][i];
		map[line][i].up = NULL;
		map[line][i].right = NULL;
		map[line][i].down = NULL;
		map[line][i].left = NULL;
	}
	return (map[line]);
}

t_map	**t_map_link(t_map **map, int line_count, int col_count)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (++j < col_count)
		{
			if (i == 0)
				map[i][j].up = NULL;
			else
				map[i][j].up = &map[i - 1][j];
			if (j >= col_count - 1)
				map[i][j].right = NULL;
			else
				map[i][j].right = &map[i][j + 1];
			if (i >= line_count - 1)
				map[i][j].down = NULL;
			else
				map[i][j].down = &map[i + 1][j];
			if (j == 0)
				map[i][j].left = NULL;
			else
				map[i][j].left = &map[i][j - 1];
			map[i][j].line_count = line_count;
			map[i][j].col_count = col_count;
		}
	}
	return (map);
}

t_map	**t_map_create(char **old_map)
{
	t_map	**map;
	int		i;
	int		j;
	int		count[2];

	if (!old_map || !*old_map)
		return (NULL);
	count[0] = 0;
	count[1] = 1;
	while (old_map[count[0]])
	{
		count[0]++;
		j  = ft_strlen(old_map[count[0]]);
		if (count[1] < j)
			count[1] = j;
	}
	map = gb_malloc((count[0] + 1) * sizeof(t_map *));
	i = -1;
	while (old_map[++i])
	{
		map[i] = gb_malloc((count[1] + 1) * sizeof(t_map));
		map[i] = t_map_fill_line(old_map, map, i);
	}
	map[i] = NULL;
	map = t_map_link(map, count[0], count[1]);
	t_map_display(map);
	return (map);
}
