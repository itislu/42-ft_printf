/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:55:31 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/25 13:08:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	n;
	int	sign;

	while (*nptr == ' ' || *nptr == '\f' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\t' || *nptr == '\v')
		nptr++;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	n = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		n = n * 10 + (*nptr - '0');
		nptr++;
	}
	return (n * sign);
}
