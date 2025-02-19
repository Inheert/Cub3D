/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:28:41 by jodiaz-a          #+#    #+#             */
/*   Updated: 2025/02/19 08:12:11 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Make sure the file pas as argument is type .cub
 */
int	ft_is_cub(const char *file)
{
	char	*p;

	p = NULL;
	if (file == NULL)
		return (0);
	p = ft_strchr(file, '.');
	if (p == NULL)
		return (0);
	if (ft_strncmp(".cub", p, 4) != 0)
		return (0);
	return (1);
}

void	init_t_file(t_file *fi)
{
	fi->no = NULL;
	fi->so = NULL;
	fi->we = NULL;
	fi->ea = NULL;
	fi->f = NULL;
	fi->c = NULL;
	fi->complet = 1;
	fi->nl = 0;
	fi->nc = 0;
	fi->line = NULL;
	fi->valid = true;
}

bool	allocate_map_rows(t_data *dt)
{
	int	i;

	dt->map = (char **)gb_malloc(sizeof(char *) * dt->fi->nl);
	if (!dt->map)
		return (false);
	i = 0;
	while (i < dt->fi->nl)
	{
		dt->map[i] = (char *)gb_malloc(sizeof(char) * (dt->fi->nc + 1));
		if (!dt->map[i])
			return (false);
		i++;
	}
	return (true);
}

void	fill_map_rows(t_data *dt)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	while (i < dt->fi->nl)
	{
		j = 0;
		while (j < dt->fi->nc)
		{
			if (dt->pos_player == k)
			{
				dt->map[i][j] = dt->vue_player;
				k++;
			}
			else
				dt->map[i][j] = dt->map_verif[k++];
			j++;
		}
		dt->map[i][j] = '\0';
		i++;
	}
}

void	str_to_table(t_data *dt)
{
	if (!allocate_map_rows(dt))
		return ;
	fill_map_rows(dt);
}
