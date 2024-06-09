/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:47:03 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/09 19:24:08 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static const char	*valid_input(const char *str);

long	ft_atol(const char *str)
{
	long	res;
	int		sign;

	if (!str)
		return (1);
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

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (*str && (*str == 32 || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error_msg("Error: Negative number");
	if (*str <= '0' && *str >= '9')
		error_msg("Error: Input is not a digit");
	number = str;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		len++;
		str++;
	}
	if (len > 10)
		error_msg("Error: Input is too long");
	return (number);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == 1)
		return (1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	my_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
}

void	print_msg(t_philo *philo, int id, char *color, char *msg)
{
	long	time;

	time = get_time() - philo->data->start_simulation;
	pthread_mutex_lock(&philo->data->write_lock);
	if ((philo->data->is_full != philo->data->number_philo) && philo->data->is_dead == 0)
	{
		printf("%s%-10ld %-3d %-30s%s\n", color, time, id, msg, RESET);
		pthread_mutex_unlock(&philo->data->write_lock);
	} 
}
