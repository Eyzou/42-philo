/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:34:18 by elo               #+#    #+#             */
/*   Updated: 2024/06/05 17:52:49 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	destroy_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philo)
	{
		pthread_mutex_destroy(&data->forks_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&data->dead_lock);
    pthread_mutex_destroy(&data->meal_lock);
    pthread_mutex_destroy(&data->write_lock);
    pthread_mutex_destroy(&data->end_lock);
	return (0);
}

void	free_all(t_data *data)
{
	free(data->philo);
}