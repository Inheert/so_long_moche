/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:03:10 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/05 20:57:44 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	close_mlx(void *ptr)
{
	static mlx_t	*smlx = NULL;

	if (!smlx && (mlx_t *)ptr)
	{
		if ((mlx_t *)ptr)
			smlx = (mlx_t *)ptr;
		return ;
	}
	if (!smlx)
		return ;
	mlx_close_window(smlx);
	mlx_terminate(smlx);
	garbage_collector(CLEAR, NULL);
	exit(0);
}

void	draw_pixels(t_map_info *map_info, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_info->slot_width && x + i < MLX_WIN_WIDTH)
	{
		j = 0;
		while (j < map_info->slot_height && y + j < MLX_WIN_HEIGHT)
		{
			mlx_put_pixel(map_info->img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	create_map_slot(t_map_info *map_info, t_map *slot)
{
	if (!map_info || !slot)
		return ;
	if (slot->slot[0] == '1')
		draw_pixels(map_info, slot->x, slot->y, WALL_SLOT_COLOR);
	else if (slot->slot[0] == '0')
		draw_pixels(map_info, slot->x, slot->y, EMPTY_SLOT_COLOR);
	else if (slot->slot[0] == 'P')
		draw_pixels(map_info, slot->x, slot->y, PLAYER_SLOT_COLOR);
	else if (slot->slot[0] == 'C')
		draw_pixels(map_info, slot->x, slot->y, COLLECTIBLE_SLOT_COLOR);
	else if (slot->slot[0] == 'E')
		draw_pixels(map_info, slot->x, slot->y, EXIT_SLOT_COLOR);
	if (slot->slot[0] == 'E')
		slot->is_end = true;
	else
		slot->is_end = false;
}

void	mlx_create_map(t_map_info *map_info)
{
	t_map	*map;
	t_map	*temp;
	int		x;
	int		y;

	map = map_info->map;
	y = 0;
	while (map)
	{
		temp = map;
		x = 0;
		while (temp)
		{
			temp->x = x;
			temp->y = y;
			x += map_info->slot_width;
			create_map_slot(map_info, temp);
			temp = temp->right;
		}
		y += map_info->slot_height;
		map = map->below;
	}
}

void	start_mlx(t_map_info *map_info)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(MLX_WIN_WIDTH, MLX_WIN_HEIGHT, "so_long", false);
	if (!mlx)
		raise_error(MLX_ERROR, NULL);
	map_info->mlx = mlx;
	raise_error(NULL, mlx);
	img = mlx_new_image(mlx, MLX_WIN_WIDTH, MLX_WIN_HEIGHT);
	if (!img)
		raise_error(MLX_IMG_ERROR, NULL);
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
		raise_error(MLX_IMG_ERROR, NULL);
	map_info->img = img;
	mlx_create_map(map_info);
	close_mlx(mlx);
	moove_player(0, 0, map_info);
	init_mlx_hooks(mlx, map_info);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	map_info++;
}
