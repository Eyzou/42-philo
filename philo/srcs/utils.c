/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:47:03 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/17 10:27:23 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static const char	*valid_input(const char *str, t_data *data);

long	ft_atol(const char *str, t_data *data)
{
	long	res;
	int		sign;

	str = valid_input(str, data);
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
	if (res > INT_MAX)
	{
		clean_all(data);
		error_msg("Error: Input is bigger than INT MAX");
	}
	return (res * sign);
}

static const char	*valid_input(const char *str, t_data *data)
{
	int			len;
	const char	*number;

	len = 0;
	while (*str && (*str == 32 || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		clean_all(data);
		error_msg("Error: Negative number");
	}
	number = str;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		len++;
		str++;
	}
	if (*str != '\0' || len > 10)
	{
		clean_all(data);
		error_msg("Error: Input is not a digit or is too long");
	}
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

	pthread_mutex_lock(&philo->data->write_lock);
	time = get_time() - philo->data->start_simulation;
	if (is_full(philo) != 0 && !(is_dead(philo)))
		printf("%s%-10ld %-3d %-30s%s\n", color, time, id, msg, RESET);
	pthread_mutex_unlock(&philo->data->write_lock);
}
