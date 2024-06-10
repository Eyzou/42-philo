/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:50:23 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/10 13:56:32 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	error_msg(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

void	clean_all(t_data *data)
{
	free(data->forks_lock);
	free(data->philo);
	free(data);
}

int	is_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	if (philo->data->is_full >= philo->data->number_philo)
	{
		pthread_mutex_unlock(&philo->data->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (0);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if ((get_time() - philo->last_meal_time) >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}
