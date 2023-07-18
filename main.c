/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:58:59 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/07 09:45:02 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_p	p;

	if (argc == 5 || argc == 6)
	{
		if (init_var(argc, argv, &p) == -1)
			return (ft_exit("Error: wrong argument format.\n"));
	}
	else
		return (ft_exit("Error: wrong number of arguments.\n"));
	p.ph = malloc(sizeof(t_philo) * p.input.nb);
	if (!p.ph)
		return (ft_exit("Error: malloc.\n"));
	if (init_philos(&p) < 0)
		return (ft_exit("Error: mutex init.\n"));
	if (init_threads(&p) < 0)
		return (ft_exit("Error: initializing threads.\n"));
	join_threads(&p);
	return (0);
}
