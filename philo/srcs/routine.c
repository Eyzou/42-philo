/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:55:21 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/03 15:18:16 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *routine(void *arg)
{
	t_philo *philo;
	pthread_t t;

	philo = (t_philo*)arg;
	if(philo->id % 2 == 0)
		my_usleep(philo->data->time_to_eat / 2);
	while (philo->data->is_dead != 1 && philo->data->is_full != 1)
	{
		pthread_create(&t, NULL, death_checker, philo->data);
		eat(philo);
		sleeping(philo, 1);
		pthread_detach(t);
		if(philo->number_meal == philo->data->number_must_eat)
		{
			pthread_mutex_lock(&philo->data->meal_lock);
			philo->data->is_full = 1;
			pthread_mutex_unlock(&philo->data->meal_lock);
			return (NULL);
		}
			return (NULL);	
	}
	return (NULL);
}

void 	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_lock[philo->r_fork]);
	print_msg(philo->data, philo->id,"has taken a fork");
	pthread_mutex_lock(&philo->data->forks_lock[philo->l_fork]);
	print_msg(philo->data, philo->id,"has taken a fork");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->meal_lock);
	my_usleep(philo->data->time_to_eat);
	philo->number_meal++;
	print_msg(philo->data, philo->id,"is eating");
	pthread_mutex_unlock(&philo->data->forks_lock[philo->r_fork]);
	pthread_mutex_unlock(&philo->data->forks_lock[philo->l_fork]);
}

void	sleeping(t_philo *philo, int time)
{
	print_msg(philo->data, philo->id,"is sleeping");
	my_usleep(philo->data->time_to_sleep/time);
	print_msg(philo->data, philo->id,"is thinking");
}

void	*death_checker(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	while(1)
	{
		pthread_mutex_lock(&philo->data->write_lock);
		if ((get_time() - philo->last_meal_time) > philo->data->time_to_die)
		{
			philo->data->is_dead = 1;
			print_msg(philo->data, philo->id,"is dead");
			pthread_mutex_unlock(&philo->data->write_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->write_lock);
		usleep(100);
	}
	return (NULL);
}

