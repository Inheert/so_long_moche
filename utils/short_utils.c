/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:11:56 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/05 21:16:49 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

char	*get_full_path(char *filename)
{
	char	*path;

	path = ft_strjoin_enhanced("src/maps/", filename);
	return (path);
}

void	check_args(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		raise_error(NO_VALID_ARGS_COUNT, NULL);
	else if (!ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))
		raise_error(NO_VALID_ARG, NULL);
	fd = open(get_full_path(argv[1]), O_RDONLY);
	if (fd < 0)
		raise_error(NO_VALID_ARG, NULL);
}

char	*ft_strjoin_enhanced(char *s1, char *s2)
{
	char	*s;
	size_t	ls1;
	size_t	ls2;

	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	s = (char *)ft_malloc(ls1 + ls2 + 1, sizeof(char));
	ft_strlcat(s, s1, ls1 + 1);
	ft_strlcat(s + ls1, s2, ls2 + 1);
	return (s);
}

ssize_t	str_ptr_len(char **str)
{
	ssize_t	len;

	if (!str)
		return (0);
	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

void	raise_error(char *error, void *ptr)
{
	static mlx_t	*mlx = NULL;

	if (ptr && (mlx_t *)ptr && !mlx)
	{
		mlx = (mlx_t *)ptr;
		return ;
	}
	if (mlx)
	{
		mlx_close_window(mlx);
		mlx_terminate(mlx);
	}
	garbage_collector(CLEAR, NULL);
	ft_printf("Error: %s\n", error);
	exit(1);
}
