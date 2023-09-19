/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:47:49 by mi                #+#    #+#             */
/*   Updated: 2023/09/19 20:26:20 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_num_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static int	ft_is_negative(int n, char *res)
{
	int	flag;

	flag = 1;
	if (n < 0)
	{
		*res = '-';
		flag = -1;
	}
	return (flag);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		sign;
	int		num;
	int		i;

	i = ft_num_len(n) - 1;
	sign = 1;
	res = (char *)malloc(ft_num_len(n) + 1);
	if (res == NULL)
		return (NULL);
	res[ft_num_len(n)] = '\0';
	if (n == 0)
	{
		res[0] = '0';
		return (res);
	}
	sign = ft_is_negative(n, res);
	while (n)
	{
		num = n % 10;
		n /= 10;
		res[i--] = (num * sign) + '0';
	}
	return (res);
}
