/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:50:23 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/07 09:45:02 by elo              ###   ########.fr       */
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
	int	i;

	i = 0;
	free(data->philo);
	while (i < data->number_philo)
	{
		pthread_mutex_destroy(&data->forks_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->end_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	free(data->forks_lock);
	free(data);
}

