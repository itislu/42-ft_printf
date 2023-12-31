/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:04:12 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/24 16:21:34 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Does not mark the new node as the end of the list by itself. */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cur;

	if (lst != NULL && new != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			cur = *lst;
			while (cur->next != NULL)
				cur = cur->next;
			cur->next = new;
		}
	}
	return ;
}
