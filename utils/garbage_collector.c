/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 07:56:02 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/05 19:08:03 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

t_garbage	*new_garbage(void *ptr)
{
	t_garbage	*garbage;

	garbage = malloc(sizeof(t_garbage));
	if (!garbage)
	{
		free(ptr);
		raise_error(MALLOC_ERROR, NULL);
	}
	garbage->content = ptr;
	garbage->next = NULL;
	return (garbage);
}

void	add_garbage(t_garbage **garbage, void *ptr)
{
	t_garbage	*new;
	t_garbage	*tmp;

	if (!*garbage)
	{
		*garbage = new_garbage(ptr);
		return ;
	}
	new = new_garbage(ptr);
	tmp = *garbage;
	while (tmp->next)
	{
		if (tmp->content == ptr)
			return ;
		tmp = tmp->next;
	}
	tmp->next = new;
}

void	clear_garbage(t_garbage **garbage)
{
	t_garbage	*next;

	if (*garbage)
	{
		while (*garbage)
		{
			next = (*garbage)->next;
			free((*garbage)->content);
			(*garbage)->content = NULL;
			free(*garbage);
			*garbage = next;
		}
		*garbage = NULL;
	}
}

void	delete_garbage(t_garbage **garbage, void *ptr)
{
	t_garbage	*tmp;
	t_garbage	*prev;

	if (!*garbage || !ptr)
		return ;
	tmp = *garbage;
	prev = NULL;
	while (tmp)
	{
		if (tmp->content == ptr)
		{
			if (prev && tmp->next)
				prev->next = tmp->next;
			else if (prev && !tmp->next)
				prev->next = NULL;
			else
				*garbage = tmp->next;
			free(tmp->content);
			tmp->content = NULL;
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	garbage_collector(t_garbage_action action, void *ptr)
{
	static t_garbage	*garbage = NULL;

	if (action == ADD)
		add_garbage(&garbage, ptr);
	else if (action == DELETE)
		delete_garbage(&garbage, ptr);
	else if (action == CLEAR)
		clear_garbage(&garbage);
}
