/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:00:59 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/12 15:13:15 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <stdbool.h>

typedef struct s_input
{
	int				nb;
	bool			end;
	long int		tm_die;
	long int		tm_eat;
	long int		tm_sleep;
	long int		nb_must_eat;
	long int		tm_start_mil;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	msg_mutex;
	pthread_mutex_t	meal_tm;
	pthread_t		control;
}	t_input;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long int		i_eat;
	long int		last_eaten;
	bool			done_eating;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	*fork_r;
	t_input			*input_dup;
}	t_philo;

typedef struct s_p
{
	t_philo			*ph;
	t_input			input;
}	t_p;

/* main.c */
int			main(int argc, char **argv);

/* utils.c */
int			ft_atoi(const char *str);
int			is_a_digit(int nb);
void		ft_putstr_fd(char *s, int fd);

/* utils2.c */
long int	gettime(void);
int			ft_exit(char *str);
void		init_start_tm(t_p *p);
void		ft_sleep(long int total_sleep);

/* utils3.c */
void		destroy_mutx(t_p *p, int pos);
void		destroy_mutfork(t_p *p, int pos);
void		destroy_joining(t_p *p, int pos);

/* init.c */
int			init_var(int argc, char **argv, t_p *p);
int			init_threads(t_p *p);
int			init_philos(t_p *p);
void		destroy_mut(t_p *p);
int			join_threads(t_p *p);

/* routine_alone.c */
void		*one_ph_routine(void *data);

/* routine.c */
void		*ph_routine(void *data);
void		unlock_m(t_philo *ph, int pos);

/* control.c */
void		*check_isdead(void *data);
bool		end_sim(t_p *p);
bool		someone_dead(t_input *input);
bool		finished_eating(t_p *p);

/* log_msg.c */
int			msg_log(t_philo *ph, int i, char *str);
void		msg_dead(t_philo *ph, char *str);

#endif