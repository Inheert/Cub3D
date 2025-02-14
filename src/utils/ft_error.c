/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:29:59 by tclaereb          #+#    #+#             */
/*   Updated: 2025/02/14 05:50:12 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_window(t_cub *cub)
{
	mlx_close_window(cub->mlx);
	mlx_terminate(cub->mlx);
	if (cub->north_texture)
		mlx_delete_texture(cub->north_texture);
	if (cub->south_texture)
		mlx_delete_texture(cub->south_texture);
	if (cub->east_texture)
		mlx_delete_texture(cub->east_texture);
	if (cub->west_texture)
		mlx_delete_texture(cub->west_texture);
	gb_free_all();
	exit(0);
}

void	safe_close_mlx(mlx_t *mlx)
{
	static mlx_t	*_mlx = NULL;

	if (mlx && !_mlx)
		_mlx = mlx;
	else if (!mlx && _mlx)
	{
		mlx_close_window(_mlx);
		mlx_terminate(_mlx);
	}
}

void	raise_perror(char *error, bool critical)
{
	perror(error);
	if (critical == true)
	{
		safe_close_mlx(NULL);
		gb_free_all();
		exit(errno);
	}
}

void	raise_error(char *error, char *details, int exit_code, bool critical)
{
	if (error)
	{
		if (ft_strlen(error) > 0)
			write(2, error, ft_strlen(error));
		else
			write(2, "''", 2);
	}
	if (details)
	{
		write(2, ": ", 2);
		write(2, details, ft_strlen(details));
	}
	if (error || details)
		write(2, "\n", 1);
	if (critical == true)
	{
		safe_close_mlx(NULL);
		gb_free_all();
		exit(exit_code);
	}
}
