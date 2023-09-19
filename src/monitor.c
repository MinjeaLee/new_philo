/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 02:13:51 by mi                #+#    #+#             */
/*   Updated: 2023/09/19 19:46:21 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_lifespan(t_monitor *monitor, int i)
{
	if (get_time() - monitor->philo[i].last_eat > monitor->resources->lifespan)
	{
		monitor->resources->finish_program = 1;
		pthread_mutex_unlock(&monitor->resources->data_mutex);
		printf("%lld %d died\n", get_time() - monitor->resources->start_time, \
														monitor->philo[i].id + 1);
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

void	*monitor_philosophers(void *arg)
{
	t_monitor	*monitor;
	int			i;

	monitor = (t_monitor *)arg;
	while (1)
	{
		i = 0;
		while (i < monitor->resources->num_philosophers)
		{
			pthread_mutex_lock(&monitor->resources->data_mutex);
			if (check_lifespan(monitor, i))
				return (NULL);
			if (check_num_eat(monitor))
				return (NULL);
			pthread_mutex_unlock(&monitor->resources->data_mutex);
			i++;
		}
		ft_sleep(52);
	}
	return (NULL);
}
