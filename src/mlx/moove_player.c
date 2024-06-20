/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:52:19 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/06 18:29:07 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	draw(t_map *old_pos, t_map *new_pos, t_map_info *map_info)
{
	if (old_pos->is_end)
	{
		old_pos->slot[0] = 'E';
		draw_pixels(map_info, old_pos->x, old_pos->y, EXIT_SLOT_COLOR);
	}
	else
	{
		old_pos->slot[0] = '0';
		draw_pixels(map_info, old_pos->x, old_pos->y, EMPTY_SLOT_COLOR);
	}
	draw_pixels(map_info, new_pos->x, new_pos->y, PLAYER_SLOT_COLOR);
	new_pos->slot[0] = 'P';
}

void	is_player_finish(t_map *map, t_map *pos)
{
	t_map	*tmp;

	while (map)
	{
		tmp = map;
		while (tmp)
		{
			if (tmp->slot[0] == 'C')
				return ;
			tmp = tmp->right;
		}
		map = map->below;
	}
	if (pos->is_end)
		close_mlx(NULL);
}

void	moove_player(int x_dir, int y_dir, t_map_info *map_info)
{
	static t_map_info	*_map_info = NULL;
	static unsigned int	count = 0;
	t_map				*pos;

	if (!_map_info && map_info)
	{
		_map_info = map_info;
		return ;
	}
	if (!_map_info)
		return ;
	pos = get_player_pos(_map_info->map);
	if (!pos)
		return ;
	if (x_dir == 1 && pos->right->slot[0] != '1')
		draw(pos, pos->right, _map_info);
	if (x_dir == -1 && pos->left->slot[0] != '1')
		draw(pos, pos->left, _map_info);
	if (y_dir == 1 && pos->below->slot[0] != '1')
		draw(pos, pos->below, _map_info);
	if (y_dir == -1 && pos->upper->slot[0] != '1')
		draw(pos, pos->upper, _map_info);
	ft_printf("%d\n", ++count);
	is_player_finish(_map_info->map, get_player_pos(_map_info->map));
}
