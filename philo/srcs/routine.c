/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:55:21 by ehamm             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/06/04 10:00:28 by ehamm            ###   ########.fr       */
=======
/*   Updated: 2024/06/04 10:27:33 by elo              ###   ########.fr       */
>>>>>>> 20491b1309ff02b15a06598ce9887f26a5b0dcdc
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *routine(void *arg)
{
	t_philo *philo;
	pthread_t t;

	philo = (t_philo*)arg;
	if(philo->id % 2 == 0)
		my_usleep(philo->data->time_to_eat / 10);
	while (!is_dead(philo,0))
	{
		pthread_create(&t, NULL, death_checker, arg);
		eat_sleep_think(philo);
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

void 	eat_sleep_think(t_philo *philo)
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
	print_msg(philo->data, philo->id,"is sleeping");
	my_usleep(philo->data->time_to_sleep);
	print_msg(philo->data, philo->id,"is thinking");
}

int		is_dead(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (nb)
		philo->data->is_dead = 1;
	if(philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return(0);
}

void	*death_checker(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	my_usleep(philo->data->time_to_die + 10);
	pthread_mutex_lock(&philo->data->end_lock);
	while(!is_dead(philo,0) && (get_time() - philo->last_meal_time) >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		print_msg(philo->data, philo->id,"is dead");
		is_dead(philo,1);
		return (NULL);
	}
		pthread_mutex_unlock(&philo->data->dead_lock);
		usleep(500);
	return (NULL);
}

