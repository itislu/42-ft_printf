/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:16:22 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/25 13:15:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*casted_ptr_s1;
	const unsigned char	*casted_ptr_s2;
	size_t				i;

	casted_ptr_s1 = (const unsigned char *) s1;
	casted_ptr_s2 = (const unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (casted_ptr_s1[i] != casted_ptr_s2[i] || !casted_ptr_s1[i])
			return ((int) casted_ptr_s1[i] - (int) casted_ptr_s2[i]);
		i++;
	}
	return (0);
}
