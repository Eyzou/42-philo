/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:55:21 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/05 15:38:07 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	if(philo->id % 2 == 0)
		my_usleep(philo->data->time_to_eat / 2);
	while (philo->data->is_dead == 0)
	{
		eat_sleep_think(philo);
		if(philo->number_meal == philo->data->number_must_eat)
		{
			pthread_mutex_lock(&philo->data->meal_lock);
			philo->data->is_full = 1;
			pthread_mutex_unlock(&philo->data->meal_lock);
		}
	}
	return (NULL);
}

void 	eat_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_lock[philo->r_fork]);
	print_msg(philo->data, philo->id,GREEN,"has taken a fork");
	pthread_mutex_lock(&philo->data->forks_lock[philo->l_fork]);
	print_msg(philo->data, philo->id,GREEN,"has taken a fork");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->meal_lock);
	my_usleep(philo->data->time_to_eat);
	philo->number_meal++;
	print_msg(philo->data, philo->id,G_CYAN,"is eating");
	pthread_mutex_unlock(&philo->data->forks_lock[philo->r_fork]);
	pthread_mutex_unlock(&philo->data->forks_lock[philo->l_fork]);
	print_msg(philo->data, philo->id,B_BLUE,"is sleeping");
	my_usleep(philo->data->time_to_sleep);
	print_msg(philo->data, philo->id,BLUE,"is thinking");
}

// int		is_dead(t_philo *philo, int nb)
// {
// 	pthread_mutex_lock(&philo->data->dead_lock);
// 	if (nb)
// 		philo->data->is_dead = 1;
// 	if(philo->data->is_dead)
// 	{
// 		pthread_mutex_unlock(&philo->data->dead_lock);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->data->dead_lock);
// 	return(0);
// }

void	*death_checker(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	printf("philo id: %d, get time: %ld last meal time: %ld\n",philo->id,get_time(), philo->last_meal_time);
	printf("get time  - last meal time :%ld \n", (get_time()-philo->last_meal_time));
	printf("time to die :%ld \n", philo->data->time_to_die);
	my_usleep(philo->data->time_to_die + 10);
	pthread_mutex_lock(&philo->data->end_lock);
	if((get_time() - philo->last_meal_time) >= philo->data->time_to_die)
	{
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		print_msg(philo->data, philo->id,PINK,"is dead");
		return(NULL);
	}
		pthread_mutex_unlock(&philo->data->dead_lock);
		usleep(500);
	return (NULL);
}

