/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:25:55 by pjelinek          #+#    #+#             */
/*   Updated: 2025/05/09 12:35:04 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*current;

	head = NULL;
	current = NULL;
	if (!lst)
		return (NULL);
	head = ft_lstnew(f(lst->content));
	if (!head)
		return (ft_lstclear(&head, del), NULL);
	lst = lst->next;
	while (lst != NULL)
	{
		current = ft_lstnew(f(lst->content));
		if (!current)
			return (ft_lstclear(&head, del), NULL);
		ft_lstadd_back(&head, current);
		lst = lst->next;
	}
	return (head);
}
