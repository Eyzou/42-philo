/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:55:21 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/03 14:13:33 by elo              ###   ########.fr       */
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
	t_philo *philo;
	pthread_t t;

	philo = (t_philo*)arg;
	printf("philo %d\n", philo->id);
	if(philo->id % 2 == 0)
		sleeping(philo->data,2);
	while (1)// one thread for death checking
	{
		pthread_create(&t, NULL, check_death, philo->data);
		eat(philo->data);
		sleeping(philo->data, 1);
		pthread_detach(t);
		if(philo->number_meal == philo->data->number_must_eat)
			return (NULL);	
	}
	return (NULL);
}


int create_thread(t_data *data)
{
	int i;
	i = 0;
	while(i < data->number_philo)
	{
		pthread_create(&data->philo[i].t, NULL, &routine ,&data->philo[i]);
		i++;
	}
	i = 0;
	while(i < data->number_philo)
	{
		pthread_join(data->philo[i].t,NULL);
		i++;
	}
	return (0);
}

void 	eat(t_data *data)
{
	pthread_mutex_lock(&data->forks_lock[data->philo->r_fork]);
	print_msg(data, data->philo->id,"has taken a fork\n");
	pthread_mutex_lock(&data->forks_lock[data->philo->l_fork]);
	print_msg(data, data->philo->id,"has taken a fork\n");
	pthread_mutex_lock(&data->meal_lock);
	data->philo->last_meal_time = get_time();
	pthread_mutex_unlock(&data->meal_lock);
	my_usleep(data->time_to_eat);
	data->philo->number_meal++;
	print_msg(data, data->philo->id,"is eating");
	pthread_mutex_unlock(&data->forks_lock[data->philo->r_fork]);
	pthread_mutex_unlock(&data->forks_lock[data->philo->l_fork]);
}

void	sleeping(t_data *data, int time)
{
	print_msg(data, data->philo->id,"is sleeping");
	my_usleep(data->time_to_sleep/time);
	print_msg(data, data->philo->id,"is thinking");
}

void	*check_death(void *philo)
{
	t_data *data;

	data = (t_data*)philo;
	my_usleep(data->time_to_die + 1);
	if ((get_time() - data->philo->last_meal_time) > data->time_to_die)
	{
		print_msg(data, data->philo->id,"is dead");
	}
	return (NULL);
}

