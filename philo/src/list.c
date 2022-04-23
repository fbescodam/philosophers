/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 19:25:39 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/23 16:36:59 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

/**
 * Create a new list item with content
 * @param content	A pointer to any content, to add to the list
 * @return			The newly created list element, NULL on error
 */
t_list	*ph_list_new(void *content)
{
	t_list	*ret;

	ret = (t_list *)malloc(sizeof(t_list));
	if (ret)
	{
		ret->content = content;
		ret->next = NULL;
	}
	return (ret);
}

/**
 * Get the last element of a list
 * @param list	The list
 * @return		The last element
 */
t_list	*ph_list_last(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/**
 * Get the size of a list
 * @param list	The list
 * @return		The size
 */
size_t	ph_list_size(t_list *list)
{
	size_t	size;

	size = 0;
	while (list)
	{
		list = list->next;
		size++;
	}
	return (size);
}

/**
 * Add an element to the end of a list
 * @param list	A list
 * @param elem	The element to add
 */
void	ph_list_add(t_list **list, t_list *elem)
{
	if (*list)
		ph_list_last(*list)->next = elem;
	else
		*list = elem;
}

/**
 * Clear a list and free its contents
 * @param list	The list to clear
 */
void	ph_list_clear(t_list **list)
{
	t_list	*temp1;
	t_list	*temp2;

	if (list)
	{
		temp1 = *list;
		while (temp1)
		{
			temp2 = temp1->next;
			free(temp1->content);
			free(temp1);
			temp1 = temp2;
		}
		*list = NULL;
	}
}
