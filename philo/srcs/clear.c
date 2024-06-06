/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:50:23 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/06 17:08:50 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	error_msg(char *msg)
{
	printf("%s\n", msg);
	return(1);
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

