/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:14:17 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/12 10:04:28 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_isdead(void *data)
{
	t_p	*p;

	p = (t_p *)data;
	while (1)
	{
		if (finished_eating(p) == true)
			return (0);
		if (end_sim(p) == true)
			return (0);
	}
	return (0);
}

bool	finished_eating(t_p *p)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&p->input.end_mutex);
	while (p->input.nb_must_eat != -1 && p->ph[i].done_eating == true)
		i++;
	pthread_mutex_unlock(&p->input.end_mutex);
	if (i == p->input.nb)
		return (true);
	return (false);
}

bool	end_sim(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->input.nb)
	{
		pthread_mutex_lock(&p->input.meal_tm);
		if ((gettime() - p->ph[i].last_eaten) 
			> p->input.tm_die)
		{
			pthread_mutex_unlock(&p->input.meal_tm);
			pthread_mutex_lock(&p->input.end_mutex);
			p->input.end = true;
			pthread_mutex_unlock(&p->input.end_mutex);
			usleep(500);
			msg_dead(&p->ph[i], "died");
			return (true);
		}
		pthread_mutex_unlock(&p->input.meal_tm);
		i++;
	}
	return (false);
}

bool	someone_dead(t_input *input)
{
	bool	dead;

	dead = false;
	pthread_mutex_lock(&input->end_mutex);
	if (input->end == true)
		dead = true;
	pthread_mutex_unlock(&input->end_mutex);
	return (dead);
}
