/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:05:18 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/12 17:57:44 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	msg_log(t_philo *ph, int i, char *str)
{
	long int		time;

	time = gettime();
	if (time == -1) 
		return (-1);
	pthread_mutex_lock(&ph->input_dup->end_mutex);
	if (ph->input_dup->end == false)
	{
		pthread_mutex_unlock(&ph->input_dup->end_mutex);
		time -= ph->input_dup->tm_start_mil;
		pthread_mutex_lock(&ph->input_dup->msg_mutex);
		printf("%03ld %d %s\n", time, i, str);
		pthread_mutex_unlock(&ph->input_dup->msg_mutex);
		return (0);
	}
	pthread_mutex_unlock(&ph->input_dup->end_mutex);
	return (-1);
}

void	msg_dead(t_philo *ph, char *str)
{
	long int		time;

	time = gettime();
	if (time == -1)
		ft_exit("Error: gettimeofday.\n");
	if (ph->input_dup->end == true)
	{
		time -= ph->input_dup->tm_start_mil;
		pthread_mutex_lock(&ph->input_dup->msg_mutex);
		printf("%03ld %d %s\n", time, ph->id, str);
		pthread_mutex_unlock(&ph->input_dup->msg_mutex);
	}
}
