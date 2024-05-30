/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:55:21 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/30 19:48:20 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	change_state(t_data *data, int state)
{
	data->philo->state = state;
	if(data->philo->state != DEAD)
		return(state);
	else
		return (DEAD);
}

void	print_msg(t_data *data)
{
	pthread_mutex_lock(&data->write_lock);
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
		sleeping(data);
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
	change_state(data, EATING);
	data->philo->last_meal_time = get_time();
	print_msg(data, EATING);
	my_usleep(data->time_to_eat);
	pthread_mutex_unlock(&data->forks_lock[data->philo->r_fork]);
	pthread_mutex_unlock(&data->forks_lock[data->philo->l_fork]);
}

int	sleeping(t_data *data)
{
	if(change_state(data,SLEEPING))
		return(1);
	print_msg(data, SLEEPING);
	my_usleep(data->time_to_sleep);
	return(0);
}