/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:39:58 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/06 17:40:03 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	eat_sleep_think(t_philo *philo);
static bool	is_dead(t_data *data, t_philo *philo);

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->number_philo == 1)
	{
		print_msg(philo->data, philo->id, GREEN, "has taken a fork");
		return (NULL);
	}
	if (philo->id % 2 == 0)
		my_usleep(philo->data->time_to_eat / 10);
	while (1)
	{
		eat_sleep_think(philo);
		pthread_mutex_lock(&philo->data->end_lock);
		if (philo->data->is_full == philo->data->number_philo
			|| philo->data->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->data->end_lock);
			break;
		}
		pthread_mutex_unlock(&philo->data->end_lock);
	}
	return (NULL);
}

void	*death_checker(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	my_usleep(philo->data->time_to_die + 20);
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&philo->data->dead_lock);
		while (i < philo[0].data->number_philo)
		{
			// printf("philo id: %d, get time: %ld last meal time: %ld\n",
			// 	philo[i].id, get_time(), philo->last_meal_time);
			// printf("get time  - last meal time :%ld \n", (get_time()
			// 		- philo[i].last_meal_time));
			// printf("time to die :%ld \n", philo[i].data->time_to_die);
			if (is_dead(philo[i].data, &philo[i]) == true)
				return (NULL);
			i++;
		}
		pthread_mutex_unlock(&philo->data->dead_lock);
		usleep(500);
	}
	return (NULL);
}

static void	eat_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_lock[philo->r_fork]);
	print_msg(philo->data, philo->id, GREEN, "has taken a r fork");
	pthread_mutex_lock(&philo->data->forks_lock[philo->l_fork]);
	print_msg(philo->data, philo->id, GREEN, "has taken a l fork");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal_time = get_time();
	philo->number_meal++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	print_msg(philo->data, philo->id, G_CYAN, "is eating");
	my_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks_lock[philo->r_fork]);
	pthread_mutex_unlock(&philo->data->forks_lock[philo->l_fork]);
	print_msg(philo->data, philo->id, B_BLUE, "is sleeping");
	my_usleep(philo->data->time_to_sleep);
	print_msg(philo->data, philo->id, BLUE, "is thinking");
}

static bool	is_dead(t_data *data, t_philo *philo)
{
	if (data->number_must_eat > 0 && philo->number_meal >= data->number_must_eat
		&& philo->is_full == 0)
	{
		data->is_full++;
		philo->is_full = 1;
	}
	printf("id:%d, nb of meal:%d is full:%d\n",philo->id,philo->number_meal,data->is_full);
	if ((get_time() - philo->last_meal_time) >= philo->data->time_to_die)
	{
		print_msg(philo->data, philo->id, PINK, "is dead");
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (true);
	}
	return (false);
}
