/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:12:04 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/25 13:13:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putnchar_fd(char c, size_t n, int fd)
{
	size_t	written;

	written = 0;
	if (fd < 0)
		return (0);
	while (n > 0)
	{
		if (write(fd, &c, 1) == 1)
			written += 1;
		n--;
	}
	return (written);
}
