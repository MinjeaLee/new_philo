/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 01:30:26 by mi                #+#    #+#             */
/*   Updated: 2023/09/19 04:51:08 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_exit(t_philo *philo)
{
	pthread_mutex_lock(&philo->resources->data_mutex);
	if (philo->resources->finish_program == 1)
	{
		pthread_mutex_unlock(&philo->resources->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->resources->data_mutex);
	return (0);
}

void *alone_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}