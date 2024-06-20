/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:50:08 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/05 18:07:48 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	param = (void *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_mlx(NULL);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		moove_player(0, -1, NULL);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		moove_player(0, 1, NULL);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		moove_player(-1, 0, NULL);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		moove_player(1, 0, NULL);
}

void	init_mlx_hooks(mlx_t *mlx, t_map_info *map_info)
{
	mlx_key_hook(mlx, &ft_key_hook, map_info);
	mlx_close_hook(mlx, &close_mlx, NULL);
}
