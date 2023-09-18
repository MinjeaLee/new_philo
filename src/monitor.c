/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 02:13:51 by mi                #+#    #+#             */
/*   Updated: 2023/09/19 05:26:45 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_lifespan(t_monitor *monitor)
{
	if (get_time() - monitor->philo->last_eat > monitor->resources->lifespan)
	{
		monitor->resources->finish_program = 1;
		pthread_mutex_unlock(&monitor->resources->data_mutex);
		printf("%lld %d died\n", get_time() - monitor->resources->start_time, \
															monitor->philo->id);
		return (1);
	}
	return (0);
}

int	check_num_eat(t_monitor *monitor)
{
	if (monitor->resources->num_finished == monitor->resources-> \
													num_philosophers)
	{
		monitor->resources->finish_program = 1;
		pthread_mutex_unlock(&monitor->resources->data_mutex);
		printf("finish\n");
		return (1);
	}
	return (0);
}

void *monitor_philosophers(void *arg)
{
	t_monitor *monitor = (t_monitor *)arg;
	int i;

	while (1)
	{
		for (i = 0; i < monitor->resources->num_philosophers; i++)
		{
			pthread_mutex_lock(&monitor->resources->data_mutex);
			if (check_lifespan(monitor))
				return (NULL);
			// if (get_time() - monitor->philo->last_eat > monitor->resources->lifespan)
			// {
			// 	monitor->resources->finish_program = 1;
			// 	pthread_mutex_unlock(&monitor->resources->data_mutex);
			// 	printf("%lld %d died\n", get_time() - monitor->resources->start_time, monitor->philo->id);
			// 	return (NULL);
			// }
			if (check_num_eat(monitor))
				return (NULL);
			// if (monitor->resources->num_finished == monitor->resources->num_philosophers)
			// {
			// 	monitor->resources->finish_program = 1;
			// 	pthread_mutex_unlock(&monitor->resources->data_mutex);
			// 	printf("finish\n");
			// 	return (NULL);
			// }
			pthread_mutex_unlock(&monitor->resources->data_mutex);
		}
		ft_sleep(100);
	}
	return (NULL);
}