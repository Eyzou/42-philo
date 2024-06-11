/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:50:23 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/11 09:29:57 by ehamm            ###   ########.fr       */
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
	int	full;

	pthread_mutex_lock(&philo->data->meal_lock);
	full = philo->should_eat;
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (full);
}

int	is_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->data->dead_lock);
	dead = philo->data->is_dead;
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (dead);
}

void	print_msg_death(t_philo *philo, int id, char *color, char *msg)
{
	long	time;

	pthread_mutex_lock(&philo->data->write_lock);
	time = get_time() - philo->data->start_simulation;
	printf("%s%-10ld %-3d %-30s%s\n", color, time, id, msg, RESET);
	pthread_mutex_unlock(&philo->data->write_lock);
}
