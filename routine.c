/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:25:02 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/12 10:07:27 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_m(t_philo *ph, int pos)
{
	if (pos == 1)
		pthread_mutex_unlock(&ph->fork_l);
	if (pos == 2 || pos == 3)
	{
		pthread_mutex_unlock(ph->fork_r);
		pthread_mutex_unlock(&ph->fork_l);
	}
}

static void	ph_routine_fork(t_philo *ph)
{
	while (1)
	{
		pthread_mutex_lock(&ph->fork_l);
		msg_log(ph, ph->id, "has taken a fork");
		if (someone_dead(ph->input_dup) == true)
		{
			unlock_m(ph, 1);
			break ;
		}
		pthread_mutex_lock(ph->fork_r);
		msg_log(ph, ph->id, "has taken a fork");
		if (someone_dead(ph->input_dup) == true)
		{
			unlock_m(ph, 2);
			break ;
		}
		break ;
	}
}

static void	ph_routine_eat(t_philo *ph)
{
	while (1)
	{
		msg_log(ph, ph->id, "is eating");
		pthread_mutex_lock(&ph->input_dup->meal_tm);
		ph->last_eaten = gettime();
		ph->i_eat++;
		pthread_mutex_unlock(&ph->input_dup->meal_tm);
		ft_sleep(ph->input_dup->tm_eat);
		if (someone_dead(ph->input_dup) == true)
		{
			unlock_m(ph, 3);
			break ;
		}
		pthread_mutex_unlock(ph->fork_r);
		pthread_mutex_unlock(&ph->fork_l);
		break ;
	}
}

static void	ph_routine_sleep(t_philo *ph)
{
	while (1)
	{
		msg_log(ph, ph->id, "is sleeping");
		ft_sleep(ph->input_dup->tm_sleep);
		if (someone_dead(ph->input_dup) == true)
			break ;
		msg_log(ph, ph->id, "is thinking");
		break ;
	}
}

void	*ph_routine(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	if ((ph->id % 2) == 0)
		usleep(ph->input_dup->tm_eat * 1000 / 10); 
	while (someone_dead(ph->input_dup) == false)
	{
		ph_routine_fork(ph);
		ph_routine_eat(ph);
		if (ph->i_eat == ph->input_dup->nb_must_eat)
		{
			pthread_mutex_lock(&ph->input_dup->end_mutex);
			ph->done_eating = true;
			pthread_mutex_unlock(&ph->input_dup->end_mutex);
			break ;
		}
		ph_routine_sleep(ph);
	}
	return (0);
}
