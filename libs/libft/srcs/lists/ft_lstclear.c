/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:13:07 by gudias            #+#    #+#             */
/*   Updated: 2021/10/27 12:13:11 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;
	t_list	*list;

	if (lst)
	{
		list = *lst;
		while (list)
		{	
			next = list->next;
			del(list->content);
			free(list);
			list = next;
		}
		*lst = NULL;
	}
}
