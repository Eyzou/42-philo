/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:55:21 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/28 21:31:39 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int sleep(t_data *data)
{
	if (data->time_to_eat )
	while(i < data->number_philo)
	{
		if(pthread_create(&t[i], NULL, routine(data) ,data->philo) != 0)
			printf("Error creating thread\n");
		i++;
	}
	
	return (0);
}

void *routine(void  *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	while(1)
	{
		if (philo->is_full)
			break;
	}
	return (NULL);
}


int create_thread(t_data *data)
{
	pthread_t t[data->number_philo];
	int i;
	while(i < data->number_philo)
	{
		if(pthread_create(&t[i], NULL, routine(data) ,data->philo) != 0)
			printf("Error creating thread\n");
		i++;
	}
	
	return (0);
}

int join_thread(t_data *data)
{
	pthread_t t[data->number_philo];
	int i;
	while(i < data->number_philo)
	{
		if(pthread_join(t[i],NULL) != 0)
			printf("Error joining thread\n");
		i++;
	}

}