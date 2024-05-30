/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:55:21 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/29 13:38:31 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *routine(void *arg)
{
	t_data *data;
	data = (t_data*)arg;
	if(data->philo->id % 2 = 0)
		my_sleep(data->time_to_eat / 2);
	while (philo->philo->state != DEAD)
	{
		if(get_time() - philo->last_meal_time > philo->time_to_die)
		{
			change_state(philo,DEAD);
			return (NULL);
		}
		else
}

int create_thread(t_data *data)
{
	pthread_t t[data->number_philo];
	int i;
	i = 0;
	while(i < data->number_philo)
	{
		pthread_create(&t[i], NULL, routine(data) ,(void *)&i);
		i++;
	}
	i = 0;
	while(i < data->number_philo)
	{
		pthread_join(t[i],NULL);
		i++;
	}
	return (0);
}

void eat(void *philo)
{
	//nombre pair commence a manger
	if(data->id % 2 = 0)
	{
		pthread_mutex_lock(&data->r_fork);
		pthread_mutex_lock(&data->l_fork);	
	}
	pthread_mutex_lock(&data->r_fork);
	pthread_mutex_lock(&data->l_fork);
	
	pthread_mutex_unlock(&data->r_fork);
	pthread_mutex_unlock(&data->l_fork);
}

int	sleep(t_data *data)
{}

int think(t_data *data)
{
	change_state(data->philo,THINKING);
	if (change_state(data->philo) == DEAD)
		return(1);
}