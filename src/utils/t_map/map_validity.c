/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:08:59 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/05 21:06:52 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	recursive_path_checker(t_map *map, int *is_path_valid)
{
	if (!map || map->slot[0] == '1')
		return ;
	else if (map->slot[0] == 'E')
		*is_path_valid = 1;
	map->slot[0] = '1';
	recursive_path_checker(map->left, is_path_valid);
	recursive_path_checker(map->right, is_path_valid);
	recursive_path_checker(map->upper, is_path_valid);
	recursive_path_checker(map->below, is_path_valid);
}

int	is_ennemy_accessible(t_map *map)
{
	t_map	*temp;

	while (map)
	{
		temp = map;
		while (temp)
		{
			if (temp->slot[0] == 'C')
				return (0);
			temp = temp->right;
		}
		map = map->below;
	}
	return (1);
}

int	is_valid_path_exist(t_map *map)
{
	t_map	*start_pos;
	int		is_path_valid;

	start_pos = get_player_pos(map);
	is_path_valid = 0;
	recursive_path_checker(start_pos, &is_path_valid);
	is_path_valid = is_ennemy_accessible(map);
	return (is_path_valid);
}

int	is_char_missing(t_map *map, t_map *tmp)
{
	t_check_symbols	check_symbols;

	tmp = map;
	check_symbols.is_exit_exist = 0;
	check_symbols.is_start_exist = 0;
	check_symbols.is_collectible_exist = 0;
	while (tmp)
	{
		if (tmp->slot[0] == 'E')
			check_symbols.is_exit_exist = 1;
		else if (tmp->slot[0] == 'P')
			check_symbols.is_start_exist = 1;
		else if (tmp->slot[0] == 'C')
			check_symbols.is_collectible_exist = 1;
		tmp = tmp->right;
		if (!tmp)
		{
			map = map->below;
			tmp = map;
		}
	}
	if (!check_symbols.is_exit_exist || !check_symbols.is_start_exist
		|| !check_symbols.is_collectible_exist)
		return (1);
	return (0);
}

int	is_valid_char_number(t_map *map)
{
	int		e;
	int		p;
	t_map	*tmp;

	e = 0;
	p = 0;
	while (map)
	{
		tmp = map;
		while (tmp)
		{
			if (tmp->slot[0] == 'E')
				e++;
			else if (tmp->slot[0] == 'P')
				p++;
			tmp = tmp->right;
		}
		map = map->below;
	}
	if (e != 1 || p != 1)
		return (0);
	return (1);
}
