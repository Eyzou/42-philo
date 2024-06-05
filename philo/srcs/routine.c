/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:55:21 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/05 18:26:07 by elo              ###   ########.fr       */
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
	int i;

	i=0;
	philo = (t_philo*)arg;
	my_usleep(philo->data->time_to_die + 10);
	printf("philo id: %d, get time: %zu last meal time: %llu\n",philo->id,get_time(), philo->last_meal_time);
	printf("get time  - last meal time :%llu \n", (get_time()-philo->last_meal_time));
	printf("time to die :%llu \n", philo->data->time_to_die);
	while(1)
	{
		while(i < philo[0].data->number_philo)
		{
			if((get_time() - philo[i].last_meal_time) >= philo->data->time_to_die)
			{
				pthread_mutex_lock(&philo->data->dead_lock);
				philo->data->is_dead = 1;
				pthread_mutex_unlock(&philo->data->dead_lock);
				print_msg(philo[i].data, philo[i].id,PINK,"is dead");
				return(NULL);
			}
			if(philo[i].number_meal >= philo->data->number_must_eat)
			{
				pthread_mutex_lock(&philo->data->meal_lock);
				philo->data->is_full++;
				pthread_mutex_unlock(&philo->data->meal_lock);
			}
			if(philo->data->is_full == philo->data->number_philo)
				return (NULL);
			i++;
		}
		usleep(500);
	}
}

