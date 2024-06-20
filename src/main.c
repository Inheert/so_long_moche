/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:56:25 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/05 15:47:30 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_map_info	*map_info;

	check_args(argc, argv);
	map_info = map_parsing(argv[1]);
	start_mlx(map_info);
	map_info++;
	garbage_collector(CLEAR, NULL);
	return (0);
}
