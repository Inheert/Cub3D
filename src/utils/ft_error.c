/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:29:59 by tclaereb          #+#    #+#             */
/*   Updated: 2025/02/19 08:49:46 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	delete_textures(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub->north_texture)
		mlx_delete_texture(cub->north_texture);
	if (cub->south_texture)
		mlx_delete_texture(cub->south_texture);
	if (cub->east_texture)
		mlx_delete_texture(cub->east_texture);
	if (cub->west_texture)
		mlx_delete_texture(cub->west_texture);
	if (cub->game_img)
		mlx_delete_image(cub->mlx, cub->game_img);
}

void	close_window(t_cub *cub)
{
	if (!cub)
		return ;
	mlx_close_window(cub->mlx);
	mlx_terminate(cub->mlx);
	delete_textures(cub);
	gb_free_all();
	exit(0);
}

void	safe_close_mlx(t_cub *cub)
{
	static t_cub	*_cub = NULL;

	if (cub && !_cub)
		_cub = cub;
	else if (!cub && _cub)
	{
		mlx_close_window(_cub->mlx);
		mlx_terminate(_cub->mlx);
		delete_textures(_cub);
	}
}

void	raise_perror(char *error, bool critical)
{
	write(2, "Error:\n", 7);
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
	write(2, "Error:\n", 7);
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
