/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:12:14 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/25 13:13:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putnstr_fd(const char *s, size_t n, int fd)
{
	size_t	len;
	ssize_t	written;

	written = 0;
	if (s == NULL || n == 0 || fd < 0)
		return (0);
	len = ft_strlen(s);
	if (len > n)
		len = n;
	written = write(fd, s, len);
	if (written < 0)
		written = 0;
	return ((size_t) written);
}
