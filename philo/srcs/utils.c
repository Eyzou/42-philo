/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:47:03 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/28 15:30:19 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 +(*str - '0');
		str++;
	}
	return (res * sign);
}

long	get_time(void) // return time in milliseconds
{
	struct timeval time;
	if(gettimeofday(&time, NULL) == 1);
		return(1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void my_usleep(long milliseconds)
{
	long start;
	
	start = get_time();
	while((get_time() - start) < milliseconds)
		uspleed(500);
}