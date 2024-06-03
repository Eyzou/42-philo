/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:47:03 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/03 16:25:05 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static const char *valid_input(const char *str);

long ft_atol(const char *str)
{
	long res;
	int sign;

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
		res = res * 10 + (*str - '0');
		str++;
	}
	if (res > 2147483647)
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
	if (len > 10)
		error_msg("Error: Input is too long\n");
	return (number);
}

long get_time(void) // return time in milliseconds
{
	struct timeval time;
	if (gettimeofday(&time, NULL) == 1)
		return (1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void my_usleep(int milliseconds)
{
	int start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
}

void	print_msg(t_data *data, int id, char *msg)
{
	long time;
	time = get_time() - data->start_simulation;
	pthread_mutex_lock(&data->write_lock);
	printf("%ld %d %s\n", time, id, msg);
	pthread_mutex_unlock(&data->write_lock);
}

void error_msg(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

