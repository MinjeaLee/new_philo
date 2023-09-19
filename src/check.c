/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 01:30:26 by mi                #+#    #+#             */
/*   Updated: 2023/09/19 22:19:43 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_min_max(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = ft_atoi(argv[i]);
		if (j < 1 || j > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	check_overflow(int argc, char **argv)
{
	char	*tmp;
	int		i;

	i = 1;
	while (i < argc)
	{
		tmp = ft_itoa(ft_atoi(argv[i]));
		if (ft_strcmp(tmp, argv[i]))
		{
			free(tmp);
			return (0);
		}
		free(tmp);
		i++;
	}
	return (1);
}

int	checksum(int argc, char **argv)
{
	if (check_digit(argc, argv) == 0)
		return (0);
	if (check_min_max(argc, argv) == 0)
		return (0);
	if (check_overflow(argc, argv) == 0)
		return (0);
	return (1);
}

