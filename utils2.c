/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:32:13 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/12 17:55:29 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	gettime(void)
{
	struct timeval	tv;
	long int		time;

	time = 0;
	if (gettimeofday(&tv, NULL) == 0)
		time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	else
		ft_exit("Error: gettimeofday.\n");
	return (time);
}

int	ft_exit(char *str)
{
	ft_putstr_fd(str, 2);
	return (-1);
}

void	init_start_tm(t_p *p)
{
	struct timeval	tv;
	int				i;

	if (gettimeofday(&tv, NULL) == 0)
	{
		p->input.tm_start_mil = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		i = -1;
		while (++i < p->input.nb)
			p->ph[i].last_eaten = p->input.tm_start_mil;
	}
	else
		ft_exit("Error: gettimeofday.\n");
}

void	ft_sleep(long int total_sleep)
{
	long int	timer;

	timer = gettime() + total_sleep;
	while (gettime() < timer)
		usleep(500);
}
