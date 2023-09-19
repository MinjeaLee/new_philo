/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 01:32:55 by mi                #+#    #+#             */
/*   Updated: 2023/09/19 17:35:12 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo)
{
	take_forks(philo);
	print_status(philo, "is eating");
	ft_sleep(philo->resources->eat_duration);
	drop_forks(philo);
	pthread_mutex_lock(&philo->resources->data_mutex);
	philo->last_eat = get_time();
	if (philo->resources->finish_program)
	{
		pthread_mutex_unlock(&philo->resources->data_mutex);
		return (1);
	}
	philo->num_eat++;
	if (philo->num_eat == philo->resources->min_eat_count)
	{
		philo->finish_eat = 1;
		philo->resources->num_finished++;
		pthread_mutex_unlock(&philo->resources->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->resources->data_mutex);
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_sleep(philo->resources->sleep_duration);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->resources->data_mutex);
	if (philo->resources->finish_program)
	{
		pthread_mutex_unlock(&philo->resources->data_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->resources->data_mutex);
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
