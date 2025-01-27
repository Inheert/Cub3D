/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:59:03 by jodiaz-a          #+#    #+#             */
/*   Updated: 2025/01/27 08:26:24 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char *p, t_data *dt, int i)
{
	static int	player = 0;

	if (player == 0 && (*p == 'E' || *p == 'W' || *p == 'N' || *p == 'S'))//Pas plus d'un jouer
		return (player++, dt->pos_player = i, dt->vue_player = *p, 1);
	else if ((*p == 'E' || *p == 'W' || *p == 'N' || *p == 'S'))
		return (dt->fi->valid = false, 2);

	if (*p == '1' || *p == '0' || *p == ' '|| *p == '\n')
		return (1);
	return (dt->fi->valid = false, 2);
}

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
			dt->fi->nc = i;//take the longest line as reference.
		gb_free(line1);
		line1 = get_next_line_bonus(fd1);
		if (!line1 || line1[0] == '\n' || !ft_strchr(line1, '1'))
			break ;
	}
	if (line1)
		gb_free(line1);
	// printf("lines; %i\nrows; %i\n", dt->fi->nl, dt->fi->nc);
	if (dt->fi->nl < 3 && dt->fi->nc < 3)
		return (false);
	else
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
	int		j;
	int		is_player_output;

	dt->pos_player = 0;
	map = gb_malloc(sizeof(char) * ((dt->fi->nl * dt->fi->nc) + 1));
	if (!map)
		return (printf("get_map 1\n"), NULL);
	i = 0;
	while (i < (dt->fi->nl * dt->fi->nc))
	{
		j = 0;
		while (dt->fi->line[j])// a regarder '\n'
		{
			is_player_output = is_player(&dt->fi->line[j], dt, i);
			if (is_player_output == 2)
				return (printf("get_map 2\n"), NULL);
			if (dt->fi->line[j] == '\n' && (dt->fi->line[j - 1] == ' ' || dt->fi->line[j - 1] == '1'))
				map[i++] = '1', j++;
			else
				map[i++] = dt->fi->line[j++];
		}
		while (j < dt->fi->nc)
		{
			map[i++] = '1';
			j++;
		}
		gb_free(dt->fi->line);
		dt->fi->line = get_next_line_bonus(fd);
		if ((!dt->fi->line && ((dt->fi->nl * dt->fi->nc)) == i) || dt->fi->line[0] == '\n'  || !ft_strchr(dt->fi->line, '1'))
			break;
		else if (!dt->fi->line )
			return (printf("get_map 3\n%i char on the map\n%i char on gc_malloc\n", i, (dt->fi->nl * dt->fi->nc)), gb_free(map), NULL);
	}
	map[i] = '\0';
	// printf("get_map 4\n%i chars on the map\n%i char in the gb_malloc \nvalid: %d\n", i, (dt->fi->nl * dt->fi->nc),dt->fi->valid);
	return (map);
}

 /**
  *
  */
bool	read_map(char *line, char *line1, int fd, int fd1, t_data *dt)
{
	if (dimetions_for_map(line1, fd1, dt) == false)
		return (raise_error("Error\n", "dimetions_for_map.\n", 1, true), 0);
	dt->fi->line = line;
	dt->map_verif = get_map(dt, fd);
	if (!dt->map_verif)
		return (raise_error("Error\n", "Not valid map.\n", 1, true), 0);
	if (flood_fill(dt, dt->pos_player) == 1)
		return (raise_error("Error\n", " read_map 2 NULL.\n", 1, true), 0);

	return (true);
}
