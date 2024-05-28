/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:55:21 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/28 16:09:02 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine(t_data *data)
{
	

}

int create_thread(t_data *data)
{
	pthread_t t[data->number_philo];
	int i;
	while(i < data->number_philo)
	{
		pthread_create(&t[i], NULL, routine(data) ,data->philo);
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
		pthread_join(t[i],NULL);
		i++;
	}

}