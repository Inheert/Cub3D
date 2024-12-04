/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:29:59 by tclaereb          #+#    #+#             */
/*   Updated: 2024/12/04 12:51:37 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raise_perror(char *error, int critical)
{
	perror(error);
	if (critical == 1)
	{
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
		gb_free_all();
		exit(exit_code);
	}
}
