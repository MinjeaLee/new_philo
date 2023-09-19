/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:39:38 by mi                #+#    #+#             */
/*   Updated: 2023/09/19 17:26:39 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->resources->num_philosophers == 1)
		return (alone_philo(philo));
	if (philo->id % 2 == 0)
		ft_sleep(philo->resources->eat_duration - 100);
	while (1)
	{
		if (philo_eat(philo))
			break ;
		pthread_mutex_lock(&philo->resources->data_mutex);
		if (philo->resources->finish_program)
		{
			pthread_mutex_unlock(&philo->resources->data_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->resources->data_mutex);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	start_philosopher_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->resources->num_philosophers)
	{
		pthread_create(&philo[i].thread, NULL, philosopher_routine, &philo[i]);
		i++;
	}
}

void	clean_up(t_philo *philo, t_resources *resources)
{
	int	i;

	i = 0;
	while (i < resources->num_philosophers)
		pthread_join(philo[i++].thread, NULL);
	i = 0;
	while (i < resources->num_philosophers)
		pthread_mutex_destroy(&resources->fork[i++]);
	pthread_mutex_destroy(&resources->data_mutex);
	pthread_mutex_destroy(&resources->print_mutex);
	free(resources->fork);
	free(philo);
	free(resources);
}

int	main(int argc, char **argv)
{
	t_resources	*resources;
	t_philo		*philo;
	t_monitor	monitor;

	if (argc < 5 || argc > 6)
		return (1);
	resources = init_resources(argc, argv);
	if (!resources)
		return (1);
	philo = init_philo(resources);
	if (!philo)
		return (1);
	monitor.philo = philo;
	monitor.resources = resources;
	start_philosopher_threads(philo);
	pthread_create(&monitor.thread, NULL, monitor_philosophers, &monitor);
	pthread_join(monitor.thread, NULL);
	clean_up(philo, resources);
	return (0);
}
