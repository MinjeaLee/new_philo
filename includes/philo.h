/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:29:25 by mi                #+#    #+#             */
/*   Updated: 2023/09/19 22:36:38 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>

typedef struct s_resources
{
	int				num_philosophers;
	int				lifespan;
	int				eat_duration;
	int				sleep_duration;
	int				min_eat_count;
	int				num_finished;
	int				finish_program;
	long long		start_time;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*fork;
}	t_resources;

typedef struct s_philo
{
	int				id;
	int				num_eat;
	int				finish_eat;
	long long		last_eat;
	long long		start_eat;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_resources		*resources;
}	t_philo;

typedef struct s_monitor
{
	t_resources	*resources;
	t_philo		*philo;
	pthread_t	thread;
}	t_monitor;

// utils.c
void		*alone_philo(t_philo *philo);
void		print_status(t_philo *philo, char *status);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
int			ft_isdigit(int c);
int			ft_strcmp(const char *str1, const char *str2);

//time.c
long long	get_time(void);
void		ft_sleep(int time);

// init.c
void		init_config(t_resources *resources, int argc, char **argv);
t_philo		*init_philo(t_resources *resources);
t_resources	*init_resources(int argc, char **argv);

// check.c
int			checksum(int argc, char **argv);

// status.c
int			philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);

//monitor.c
void		*monitor_philosophers(void *arg);

#endif