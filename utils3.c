/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:36:27 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/12 17:56:22 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutx(t_p *p, int pos)
{
	if (pos == 1)
		pthread_mutex_destroy(&p->input.msg_mutex);
	if (pos == 2)
	{
		pthread_mutex_destroy(&p->input.msg_mutex);
		pthread_mutex_destroy(&p->input.end_mutex);
	}
	free(p->ph);
}

void	destroy_mutfork(t_p *p, int pos)
{
	int	i;

	pthread_mutex_destroy(&p->input.msg_mutex);
	pthread_mutex_destroy(&p->input.end_mutex);
	pthread_mutex_destroy(&p->input.meal_tm);
	i = 0;
	while (i < pos)
	{
		pthread_mutex_destroy(&p->ph[i].fork_l);
		i++;
	}
	free(p->ph);
}

void	destroy_joining(t_p *p, int pos)
{
	int	i;

	i = 0;
	while (i < pos)
	{
		if (pthread_join(p->ph[i].thread, NULL) != 0)
		{
			destroy_mutfork(p, pos);
			ft_exit("Error: joining pthread.\n");
		}
		i++;
	}
	pthread_mutex_destroy(&p->input.msg_mutex);
	pthread_mutex_destroy(&p->input.end_mutex);
	pthread_mutex_destroy(&p->input.meal_tm);
	i = 0;
	while (i < pos)
	{
		pthread_mutex_destroy(&p->ph[i].fork_l);
		i++;
	}
	free(p->ph);
}
