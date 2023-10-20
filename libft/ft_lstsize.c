/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:08:06 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/25 13:11:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		n;
	t_list	*cur;

	if (lst == NULL)
		return (0);
	n = 0;
	cur = lst;
	while (cur != NULL)
	{
		cur = cur->next;
		n++;
	}
	return (n);
}
