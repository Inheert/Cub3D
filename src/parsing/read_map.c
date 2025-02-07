/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:59:03 by jodiaz-a          #+#    #+#             */
/*   Updated: 2025/02/07 13:57:01 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	dimetions_for_map(char *line1, int fd1, t_data *dt)
{
	int	i;

	while (line1)
	{
		dt->fi->nl++;
		i = 0;
		while (line1[i])
			i++;
		if (i > dt->fi->nc)
			dt->fi->nc = i;
		gb_free(line1);
		line1 = get_next_line_bonus(fd1);
		if (!line1 || line1[0] == '\n' || !ft_strchr(line1, '1'))
			break ;
	}
	if (line1)
		gb_free(line1);
	if ((dt->fi->nl < 3 && dt->fi->nc < 3)
		|| (dt->fi->nl > 600 && dt->fi->nc > 600))
		return (false);
	else
		return (true);
}

char	*fill_map_row(char *map, t_data *dt, int *i)
{
	int	j;
	int	is_player_output;

	j = 0;
	while (dt->fi->line[j])
	{
		is_player_output = is_player(&dt->fi->line[j], dt, *i);
		if (is_player_output == 2)
			return (NULL);
		if (dt->fi->line[j] == '\n'
			&& (dt->fi->line[j - 1] == ' '
				|| dt->fi->line[j - 1] == '1'))
		{
			map[(*i)++] = ' ';
			j++;
		}
		else
			map[(*i)++] = dt->fi->line[j++];
	}
	while (j < dt->fi->nc)
	{
		map[(*i)++] = ' ';
		j++;
	}
	return (map);
}

bool	handle_new_line(t_data *dt, int fd, char *map, int i)
{
	gb_free(dt->fi->line);
	dt->fi->line = get_next_line_bonus(fd);
	if ((!dt->fi->line && (dt->fi->nl * dt->fi->nc) == i)
		|| dt->fi->line[0] == '\n' || !ft_strchr(dt->fi->line, '1'))
		return (false);
	else if (!dt->fi->line)
	{
		gb_free(map);
		return (false);
	}
	return (true);
}

/**
 * Problema en esta funcion llenar de 1 los espacion vacios
 * cuando las linea es mas corta que la mas grande
 */
char	*get_map(t_data *dt, int fd)
{
	char	*map;
	int		i;

	dt->pos_player = 0;
	map = gb_malloc(sizeof(char) * ((dt->fi->nl * dt->fi->nc) + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < (dt->fi->nl * dt->fi->nc))
	{
		map = fill_map_row(map, dt, &i);
		if (!map)
			return (NULL);
		if (!handle_new_line(dt, fd, map, i))
			break ;
	}
	map[i] = '\0';
	return (map);
}

bool	read_map(char *line, char *line1, int tfd[2], t_data *dt)
{
	int	i;

	if (dimetions_for_map(line1, tfd[1], dt) == false)
		return (raise_error("Error\n", "dimetions_for_map.\n", 1, true), 0);
	dt->fi->line = line;
	dt->map_verif = get_map(dt, tfd[0]);
	if (!dt->map_verif)
		return (raise_error("Error\n", "Not valid map.\n", 1, true), 0);
	if (flood_fill(dt, dt->pos_player) == 1)
		return (raise_error("Error\n", " map open.\n", 1, true), 0);
	i = 0;
	while (dt->map_verif[i])
	{
		if (dt->map_verif[i] == '0')
			if (flood_fill(dt, i) == 1)
				return (raise_error("Error\n", " map open.\n", 1, true), 0);
		i++;
	}
	return (true);
}
