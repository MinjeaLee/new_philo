/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:52:23 by mi                #+#    #+#             */
/*   Updated: 2023/09/19 05:34:11 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 0x9 && str[i] <= 0xd))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->resources->data_mutex);
	if (philo->resources->finish_program != 1)
	{	
		pthread_mutex_lock(&philo->resources->print_mutex);
		printf("%lld %d %s\n", get_time() - philo->resources->start_time, \
														philo->id + 1, status);
		pthread_mutex_unlock(&philo->resources->print_mutex);
	}
	pthread_mutex_unlock(&philo->resources->data_mutex);
}
