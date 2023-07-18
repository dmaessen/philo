/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:53:14 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/12 12:41:15 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_a_digit(int nb)
{
	if (nb >= 0 && nb <= INT_MAX)
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	nb;

	nb = 0;
	i = 0;
	sign = 1;
	while ((str[i] == '\t') || (str[i] == '\n') || (str[i] == '\v')
		|| (str[i] == '\f') || (str[i] == '\r') || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
		return (-1);
	while (str[i])
	{
		if ((str[i] >= 48 && str[i] <= 57))
			nb = (nb * 10) + (str[i] - 48);
		else
			return (-1);
		if (nb > INT_MAX)
			return (-1);
		i++;
	}
	return ((int)(sign * nb));
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
