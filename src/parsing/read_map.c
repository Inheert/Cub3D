/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:59:03 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/12/04 12:16:59 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

/**
 * En la primera y la ultima linea no debe de haber '0'
 * 
 * No debe de haber mas 
 */
bool	good_char(char *p, t_data *dt)
{
	static int	player = 0;
	static int	line_in_map = 0;

	if ((line_in_map == 0 || line_in_map == (dt->fi->nl - 1))//first and last line in the map
			&& ft_isgraph(*p) && *p != '1')
		return (true);
	else if ((line_in_map == 0 || line_in_map == (dt->fi->nl - 1))
			&& ft_isgraph(*p) && *p != '1')
		return (dt->if->valid = false, false)

	if (!player && (*p == 'E' || *p == 'W' || *p == 'N' || *p == 'S'))//Pas plus d'un jouer
		return (player++, true);
	else if (player && (*p == 'E' || *p == 'W' || *p == 'N' || *p == 'S'))
		return (dt->if->valid = false, false);
		
	if (*p == '1' || *p == '0' || !ft_isgraph(*p))//Seulement char valid.
		return (true);

	return (dt->if->valid = false, false);
}

/**
 * line is delimitated by a 1 before and after any other char.
 * the line has only valid char 
 * 
 */
// bool	is_maps_line_validated(t_data *dt)
// {
// 	int			i;
// 	char		*left;
// 	char		*right;

// 	right = NULL; 
// 	i = 0;
// 	while (dt->fi->line[i] && !ft_isgraph(dt->fi->line[i]))
// 		i++;
// 	if (dt->fi->line[i] != '1')// the first char in the string is 1
// 		return (perror("Error: read_map: map not validated.\n"), false);
// 	left = &line[i];
// 	while (line[i++])// find the las 1 in the string. seg fault?
// 		if (line[i] && line[i] == '1')
// 			right = &line[i];
// 	while (left != right  && *left && *right)
// 		if (!ft_isgraph(*left) || good_char(left))
// 			left++;
// 	while (right )
		
	
// 	if (dt->fi->nl < i)
// 		dt->fi->nl = i;
// 	return (true);
// }

bool	next_line_keep_map_close(t_data *dt)
{
	int	i;

	i = 0;
	while (dt->fi->line[i])
	{
		while (dt->fi->line[i] && (dt->fi->line[i] == '1' || !ft_isgraph(dt->fi->line[i])))
			i++;
		if ((dt->fi->line[i]  && dt->fi->line[i - 1])
					&& ((dt->fi->lb[i - 1] && dt->fi->lb[i - 1] == '1')//segfault??
				|| (dt->fi->lb[1] && dt->fi->lb[1] == '1')//segfault??
				|| (dt->fi->lb[1] && dt->fi->lb[i + 1] == '1')))//segfault??
			i++;
		else if (!good_char(dt->fi->line[i]) && ft_isgraph(dt->fi->line[i]))// cambiar good char
			return (perror("Error: read_map: map not validated.\n"),false);
		if (dt->fi->line[i - 1] && dt->fi->line[i - 1] == '1')
			i++;
	}
}

/**
 * verify that the line is valid and find the longest line
 */
bool	is_maps_line_validated(t_data *dt, char *line)
{
	int			i;
	char		*left;
	char		*right;

	left = NULL;
	right = NULL; 
	i = 0;
	while (dt->fi->line[i]
			&& (!ft_isgraph(line[i]) || good_char(&line[i], dt)))
	{
		if (!left && ft_isgraph(line[i]) && line[i] != '1')// the first char in the string is 1
			return (perror("Error: read_map: map not valid.\n"), false);
		else if (!left && line[i] != '1')//find the first 1 adress
			left = &line[i];
		if (line[i] == '1')// find the last 1 adress
			right = &line[i];
		i++;
	}
	if (dt->fi->valid == false)
		return (perror("Error: read_map: map not valid.\n"), false);

	while (right && *right)// verify 1 is the las graph char in the string//
	{
		if (ft_isgraph(*right) && *right != '1')
			return (perror("Error: read_map: map not valid.\n"), false);
		right++;
	}
	return (true);
}

bool	dimetions_for_map(char *line1, int fd1, t_data *dt)
{
	int	i;
	
	dt->fi->nl = 0;
	dt->fi->nc = 0;
	while (line1)
	{
		dt->fi->nc++;
		line1 = get_next_line_bonus(fd1);
		if (!line1)
			return (perror("Error: read_map: get_next_line NULL.\n"), -1);
		i = 0;
		while (line1[i])
			i++;
		if (i > dt->fi->nl)
			dt->fi->nl = i;//take the longest line as reference.
	}
	if (!dt->fi->nl && !dt->fi->nl)
		return (true);
	else
		return (false);	
}

char	**get_a_white_map(t_data *dt)
{
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * dt->fi->nl)
	if (!map)
		return (NULL);
	i = 0;
	while (i < dt->fi->nl)
	{
		map[i] = malloc(sizeof(char) * dt->fi->nc);
		if (!map[i])
		{
            while (i-- > 0)
                free(map[i]);
            free(map);
			return (NULL);
        }
	}
	return (map);
}

 /**
  * verificar;
  * Respecto a la linea;
  * 	- cada extremo esta rodeada de 1 (derecha-izquierda).
  * 		- hay un 1 antes que cualquier otro caracter valido.
  * 		- el ultimo caracter imprimible antes del '\0' es 1.
  * 	- en la linea solo hay caracteres validos entre dos unos
  * 
  * respecto a la linea anterior (no aplica para la primera linea)
  * 	- la linea anterior tiene un 1 arriva de la linea actual
  * 		o en la posicion directamente en diagonal
  * 
  * 
  * respeto a la ultima linea aparte de lo anterior
  * 	- Entre el primer 1 y el siguiente 1 en la penultima linea 
  * 		- Tiene que haber, abajo o en diagonal hacia abajo,
  * 			en la ultima linea solo  de un uno al otro 
  * O prodria hacer
  * 	- A partir del primer caracter diferente de 1 en la penultima linea
  * 		tiene que haber un 1 abajo de cada caracter valido 
  * 
  * Explorar la idea de alane: 
  * 	-copiar el mapa y asegurarme con el personaje que no puede salir.
  * 		solucion a explorar.
  * 
  * Mejor idiea;
  * 	- copiar al mapa linea por linea.
  * 		si los caracteres son validos
  * 		y uno es el primer caracter y el ultimmo
  * 	- una vez tenga el mapa copiado 
  * 		- recorrer el mapa caracter por caracter
  * 			si el caracter es diferente de 1
  * 			miras las cuatro casillas que lo rodean si es ' '. el mapa no esta cerrado.
  * 
  * les space a l'interieur de la map sont PAS valides.
  * les spaces a 'exteriur de la map sont valides
  */
char	**read_map(char *line, int *line1, int fd, int fd1, t_data *dt)
{
	char	**map;
	
	if (!dimetions_for_map(line1, fd1, dt))
		return (NULL);
	dt->fi->valid = true;
	dt->fi->line = line;
	map = get_a_white_map(dt);
	while (1)
	{
		if ((dt->fi->valid == false || is_maps_line_validated(dt, dt->fi->line) == false)
				&& /*es la primera itteration*/)
			return (NULL);
		dt->fi->lb = ft_strdup(dt->fi->line);
		if (dt->fi->lb == NULL)
			return (NULL);


		dt->fi->lm = ft_strdup(get_next_line_bonus(fd));//linea del medio
		if (dt->fi->lm == NULL)
			return (NULL);
		if (dt->fi->valid == false || is_maps_line_validated(dt, dt->fi->lm) == false);
			return (NULL);
	
		dt->fi->la = ft_strdup(get_next_line_bonus(fd));//linea final
		if (dt->fi->la == NULL)
			return (NULL);
		if (dt->fi->valid == false || is_maps_line_validated(dt, dt->fi->la) == false);
			return (NULL);

	}
	return (map);
}
