/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:10:19 by tclaereb          #+#    #+#             */
/*   Updated: 2024/05/29 09:16:38 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/so_long.h"

static unsigned int	count_strings(char const *s, char c)
{
	unsigned int	count;
	int				is_inside;

	count = 0;
	is_inside = 0;
	while (*s)
	{
		if ((*s != c && !is_inside) || c == '\0')
		{
			count++;
			is_inside = 1;
		}
		else
			is_inside = 0;
		s++;
	}
	if (c == '\0' && count > 0)
		count--;
	return (count);
}

static char	*apply_string(const char *s, char c)
{
	char	*str;
	int		len;

	len = 0;
	while (s[len] && s[len] != c && (c != '\0' || len == 0))
		len++;
	if (len == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	garbage_collector(ADD, str);
	ft_strlcpy(str, s, len + 1);
	return (str);
}

static int	fill_result(char **result, char const *s, char c)
{
	int		i;
	int		is_inside;

	i = 0;
	is_inside = 0;
	while (*s)
	{
		if ((*s != c && !is_inside) || c == '\0')
		{
			result[i] = apply_string(s, c);
			if (!result[i++])
				return (0);
			is_inside = 1;
		}
		else
			is_inside = 0;
		s++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	count;
	char			**result;

	if (!s)
		return (NULL);
	count = count_strings(s, c);
	result = (char **)malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	garbage_collector(ADD, result);
	if (!fill_result(result, s, c))
		raise_error(MALLOC_ERROR, NULL);
	result[count] = NULL;
	return (result);
}
