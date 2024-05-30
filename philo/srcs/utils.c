/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:47:03 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/30 18:54:10 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atol(const char *str)
{
	long	res;
	int	sign;
	str = valid_input(str);

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
	if(res > 2147483647)
		error_msg("Error: Input is bigger than INT MAX\n");
	return (res * sign);
}

static const char *valid_input(const char *str)
{
	int len;
	const char *number;

	len = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error_msg("Error: Negative number\n");
	if (*str <= '0' && *str >= '9')
		error_msg("Error: Input is not a digit\n");
	number = str;
	while (*str >= '0' && *str <= '9')
	{
		len++;
		str++;
	}
	if(len > 0)
		error_msg("Error: Input is too long\n");
	return (number);
}

long	get_time(void) // return time in milliseconds
{
	struct timeval time;
	if(gettimeofday(&time, NULL) == 1)
		return(1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void my_usleep(int milliseconds)
{
	int start;
	
	start = get_time();
	while((get_time() - start) < milliseconds)
		usleep(500);
}

void 	error_msg(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

