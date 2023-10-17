/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:17:19 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/25 18:18:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	len_substr;

	if (s == NULL)
		return (NULL);
	len_substr = ft_strlen(s);
	if (len_substr <= start)
		len_substr = 0;
	else
	{
		len_substr -= start;
		if (len_substr > len)
			len_substr = len;
	}
	substr = (char *) malloc(len_substr + 1);
	if (substr == NULL)
		return (NULL);
	if (len_substr > 0)
		ft_memcpy(substr, &s[start], len_substr);
	substr[len_substr] = '\0';
	return (substr);
}
