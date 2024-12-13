/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:59:03 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/12/13 17:31:55 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char *p, t_data *dt, int i)
{
	static int	player = 0;

	if (player == 0 && (*p == 'E' || *p == 'W' || *p == 'N' || *p == 'S'))//Pas plus d'un jouer
		return (player++, dt->pos_player = i, 1);
	else if ((*p == 'E' || *p == 'W' || *p == 'N' || *p == 'S'))
		return (dt->fi->valid = false, 2);
		
	if (*p == '1' || *p == '0' || *p == ' '|| *p == '\n')
		return (1);
	printf("%c", *p);
	return (dt->fi->valid = false, 2);
}

bool	dimetions_for_map(char *line1, int fd1, t_data *dt)
{
	int	i;
	
	while (line1)
	{
		dt->fi->nl++;
		free(line1);
		line1 = get_next_line_bonus(fd1);
		if (!line1)
			break ;
		i = 0;
		while (line1[i])
			i++;
		if (i > dt->fi->nc)
			dt->fi->nc = i;//take the longest line as reference.
	}
	if (dt->fi->nl < 3 && dt->fi->nc < 3)
		return (false);
	else
		return (true);	
}

char	*get_map(t_data *dt, int fd)
{
	char	*map;
	int		i;
	int		j;
	int		is_player_output;

	dt->pos_player = 0;
	map = malloc(sizeof(char) * ((dt->fi->nl * dt->fi->nc) + 1));
	if (!map)
		return (printf("get_map 1\n"), NULL);
	i = 0;
	while (i < (dt->fi->nl * dt->fi->nc))
	{
		j = 0;
		while (dt->fi->line[j])// a regarder '\n'
		{
			is_player_output = is_player(&dt->fi->line[j], dt, i);
			if (dt->fi->line[j] && is_player_output == 2)
				return (printf("get_map 2\n"), NULL);
			map[i++] = dt->fi->line[j++];
		}
		dt->fi->line = get_next_line_bonus(fd);
		if (!dt->fi->line && ((dt->fi->nl * dt->fi->nc) - 1) == i)
			break;
		else if (!dt->fi->line)
			return (printf("get_map 3; %i\n", i), free(map), NULL);
	}
	map[i + 1] = '\0';
	printf("%s\n", map);
	return (printf("get_map 4; %i\nvalid: %d \n%s", i, dt->fi->valid,map), map);
}

 /**
  * 
  */
bool	read_map(char *line, char *line1, int fd, int fd1, t_data *dt)
{
	if (dimetions_for_map(line1, fd1, dt) == false)
		return (raise_error("Error\n", "read_map 0 NULL.\n", 1, true), 0);
	dt->fi->line = line;
	dt->map_verif = get_map(dt, fd);// a causa de esto habra que regresar un int
	if (!dt->map_verif)
		return (raise_error("Error\n", "read_map 1 NULL.\n", 1, true), 0);
	if (flood_fill(dt, dt->pos_player) == 1)
		return (raise_error("Error\n", " read_map 2 NULL.\n", 1, true), 0);
	return (true);
}
