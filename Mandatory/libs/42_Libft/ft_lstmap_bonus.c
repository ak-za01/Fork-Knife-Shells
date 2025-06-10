/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:12:04 by aakritah          #+#    #+#             */
/*   Updated: 2024/11/05 11:01:44 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*t;
	t_list	*n;
	void	*temp;

	if (!lst || !f || !del)
		return (NULL);
	t = NULL;
	while (lst)
	{
		temp = f(lst->content);
		n = ft_lstnew(temp);
		if (!n)
		{
			del(temp);
			ft_lstclear(&t, del);
			return (NULL);
		}
		ft_lstadd_back(&t, n);
		lst = lst->next;
	}
	return (t);
}
