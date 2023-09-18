/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:41:31 by mi                #+#    #+#             */
/*   Updated: 2023/09/19 04:12:30 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_config(t_resources *resources, int argc, char **argv)
{
	resources->num_philosophers = ft_atoi(argv[1]);
	resources->lifespan = ft_atoi(argv[2]);
	resources->eat_duration = ft_atoi(argv[3]);
	resources->sleep_duration = ft_atoi(argv[4]);
	if (argc == 6)
		resources->min_eat_count = ft_atoi(argv[5]);
	else
		resources->min_eat_count = -1;
}

t_philo *init_philo(t_resources *resources)
{
	t_philo *philo;
	int i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * resources->num_philosophers);
	while (i < resources->num_philosophers)
	{
		philo[i].id = i;
		philo[i].num_eat = 0;
		philo[i].last_eat = resources->start_time;
		philo[i].start_eat = resources->start_time;
		philo[i].finish_eat = 0;
		philo[i].resources = resources;
		philo[i].left_fork = &resources->fork[i];
		philo[i].right_fork = &resources->fork[(i + 1) % resources->num_philosophers];
		i++;
	}
	return (philo);
}

t_resources *init_resources(int argc, char **argv)
{
	t_resources *resources;
	int i;
	
	resources = (t_resources *)malloc(sizeof(t_resources));
	if (!resources)
		return (NULL);
	init_config(resources, argc, argv);
	resources->num_finished = 0;
	resources->finish_program = 0;
	resources->start_time = get_time();
	pthread_mutex_init(&resources->data_mutex, NULL);
	pthread_mutex_init(&resources->print_mutex, NULL);
	resources->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
													resources->num_philosophers);
	i = 0;
	while (i < resources->num_philosophers)
		pthread_mutex_init(&resources->fork[i++], NULL);
	return (resources);
}
