/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:10:45 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/12 17:55:15 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_var(int argc, char **argv, t_p *p)
{
	p->input.nb = ft_atoi(argv[1]);
	if (p->input.nb == 0)
		return (-1);
	p->input.tm_die = ft_atoi(argv[2]);
	p->input.tm_eat = ft_atoi(argv[3]);
	if (p->input.tm_eat == 0)
		return (-1);
	p->input.tm_sleep = ft_atoi(argv[4]);
	p->input.nb_must_eat = -1;
	p->input.end = false;
	if (argc == 6)
	{
		p->input.nb_must_eat = ft_atoi(argv[5]);
		if (is_a_digit(p->input.nb_must_eat) == 1)
			return (-1);
	}
	if (is_a_digit(p->input.nb) == 1
		|| is_a_digit(p->input.tm_die) == 1
		|| is_a_digit(p->input.tm_eat) == 1
		|| is_a_digit(p->input.tm_sleep) == 1)
		return (-1);
	return (0);
}

int	init_philos(t_p *p)
{
	int	i;

	if (pthread_mutex_init(&p->input.msg_mutex, NULL) != 0)
		return (destroy_mutx(p, 0), -1);
	if (pthread_mutex_init(&p->input.end_mutex, NULL) != 0)
		return (destroy_mutx(p, 1), -1);
	if (pthread_mutex_init(&p->input.meal_tm, NULL) != 0)
		return (destroy_mutx(p, 2), -1);
	i = 0;
	while (i < p->input.nb)
	{
		p->ph[i].id = i + 1;
		p->ph[i].fork_r = NULL;
		p->ph[i].i_eat = 0;
		p->ph[i].done_eating = false;
		if (pthread_mutex_init(&p->ph[i].fork_l, NULL) != 0)
			return (destroy_mutfork(p, i), -1);
		if (i == (p->input.nb - 1))
			p->ph[i].fork_r = &p->ph[0].fork_l;
		else
			p->ph[i].fork_r = &p->ph[i + 1].fork_l;
		i++;
	}
	return (0);
}

int	init_threads(t_p *p)
{
	int	i;

	init_start_tm(p);
	if (p->input.nb == 1)
	{
		p->ph->input_dup = &p->input;
		if (pthread_create(&p->ph[0].thread, NULL,
				&one_ph_routine, &p->ph[0]) != 0)
			return (destroy_mutfork(p, 1), -1);
		return (0);
	}
	i = -1;
	while (++i < p->input.nb)
	{
		p->ph[i].input_dup = &p->input;
		if (pthread_create(&p->ph[i].thread, NULL,
				&ph_routine, &p->ph[i]) != 0)
			return (destroy_joining(p, i), -1);
	}
	if (pthread_create(&p->input.control, NULL, check_isdead, p) != 0)
		return (destroy_joining(p, p->input.nb), -1);
	if (pthread_join(p->input.control, NULL) != 0)
		return (destroy_joining(p, p->input.nb), -1);
	return (0);
}

int	join_threads(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->input.nb)
	{
		if (pthread_join(p->ph[i].thread, NULL) != 0)
			return (destroy_mutfork(p, p->input.nb),
				ft_exit("Error: joining pthread.\n"));
		i++;
	}
	destroy_mut(p);
	return (0);
}

void	destroy_mut(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->input.nb)
	{
		pthread_mutex_destroy(&p->ph[i].fork_l);
		i++;
	}
	pthread_mutex_destroy(&p->input.msg_mutex);
	pthread_mutex_destroy(&p->input.meal_tm);
	pthread_mutex_destroy(&p->input.end_mutex);
	free(p->ph);
}
