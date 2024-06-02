/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:55:21 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/31 12:31:39 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_msg(t_data *data, int id, char *msg)
{
	long time;
	time = get_time() - data->philo->start_time;
	pthread_mutex_lock(&data->write_lock);
	printf("%ld %d %s\n", time, id, msg);
	pthread_mutex_unlock(&data->write_lock);
}

void *routine(void *arg)
{
	t_data *data;
	data = (t_data*)arg;
	if(data->philo->id % 2 == 0)
		my_usleep(data->time_to_eat / 2);
	while (1)
	{
		eat(data);
	}
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

void 	eat(t_data *data)
{
	pthread_mutex_lock(&data->forks_lock[data->philo->r_fork]);
	pthread_mutex_lock(&data->forks_lock[data->philo->l_fork]);
	pthread_mutex_lock(&data->meal_lock);
	data->philo->last_meal_time = get_time();
	pthread_mutex_unlock(&data->meal_lock);
	my_usleep(data->time_to_eat);
	data->philo->number_meal++;
	print_msg(data, data->philo->id,"is eating");
	pthread_mutex_unlock(&data->forks_lock[data->philo->r_fork]);
	pthread_mutex_unlock(&data->forks_lock[data->philo->l_fork]);
}
