/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:25:44 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/11 15:07:23 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdio.h>

void	add_slots_to_map(t_map **map, char *line)
{
	static ssize_t	line_len = -1;
	static t_map	*last_line = NULL;
	t_map			*new_line;
	char			**splited_line;

	new_line = NULL;
	splited_line = ft_split(line, '\0');
	if (!splited_line)
		raise_error(MALLOC_ERROR, NULL);
	if (line_len == -1)
		line_len = str_ptr_len(splited_line);
	else if (line_len != str_ptr_len(splited_line))
		raise_error(NO_VALID_MAP_LINE_LEN, NULL);
	while (*splited_line)
	{
		map_add_right(&new_line, map_new(*splited_line));
		splited_line++;
	}
	if (last_line)
		map_link_lines(last_line, new_line);
	else
		*map = new_line;
	last_line = new_line;
}

void	read_map(char *filepath, t_map **map)
{
	char	*line;
	int		fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		raise_error(NO_VALID_ARG, NULL);
	line = get_next_line(fd);
	if (!line)
		raise_error(NO_VALID_MAP, NULL);
	while (line)
	{
		garbage_collector(ADD, line);
		add_slots_to_map(map, line);
		garbage_collector(DELETE, line);
		line = get_next_line(fd);
	}
}

void	check_map_validity(t_map *map)
{
	t_map	*tmp;
	int		i;

	i = 0;
	tmp = map;
	while (tmp)
	{
		if (tmp->right && ++i)
			tmp = tmp->right;
		if (tmp->below)
			tmp = tmp->below;
		if (!tmp->right && !tmp->below)
			break ;
	}
	if (i >= MLX_MAX_MAP_WIDTH)
		raise_error(MAP_TOO_LARGE, NULL);
	if (!is_wall_valid(map))
		raise_error(NO_VALID_MAP, NULL);
	else if (is_char_missing(map, tmp))
		raise_error(MISSING_SYMBOL, NULL);
	else if (!is_valid_char_number(map))
		raise_error(TOO_MANY_SYMBOLS, NULL);
	tmp = copy_map(map);
	if (!is_valid_path_exist(tmp))
		raise_error(NO_VALID_PATH, NULL);
}

t_map_info	*map_parsing(char *filename)
{
	char		*filepath;
	int			*map_len;
	t_map_info	*map_info;

	map_info = ft_malloc(sizeof(t_map_info), 1);
	filepath = get_full_path(filename);
	read_map(filepath, &map_info->map);
	check_map_validity(map_info->map);
	map_len = get_map_len(map_info->map);
	map_info->map_width = map_len[0];
	map_info->map_height = map_len[1];
	map_info->slot_width = MLX_WIN_WIDTH / map_len[0];
	map_info->slot_height = MLX_WIN_HEIGHT / map_len[1];
	return (map_info);
}
