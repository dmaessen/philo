/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_alone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:05:44 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/12 10:08:32 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_ph_routine(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	pthread_mutex_lock(&ph->fork_l);
	msg_log(ph, 1, "has taken a fork");
	usleep(ph->input_dup->tm_die * 1000);
	pthread_mutex_unlock(&ph->fork_l);
	msg_log(ph, 1, "died");
	return (0);
}
