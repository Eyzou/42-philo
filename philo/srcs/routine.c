/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:39:58 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/11 09:22:49 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	eat_sleep_think(t_philo *philo);
static int	death_checker(t_philo *philo);

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->number_philo == 1)
	{
		print_msg(philo, philo->id, GREEN, "has taken a fork");
		return (NULL);
	}
	if (philo->id % 2 == 0)
		my_usleep(philo->data->time_to_eat/2);
	while (!(is_dead(philo)) || (is_full(philo)) != 0)
	{
		eat_sleep_think(philo);
		if (is_full(philo) == 0 || is_dead(philo) == 1)
			break ;
	}
	return (NULL);
}

static void	eat_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_lock[philo->r_fork]);
	print_msg(philo, philo->id, GREEN, "has taken a r fork");
	pthread_mutex_lock(&philo->data->forks_lock[philo->l_fork]);
	print_msg(philo, philo->id, GREEN, "has taken a l fork");
	print_msg(philo, philo->id, G_CYAN, "is eating");
	pthread_mutex_lock(&philo->data->time_lock);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->time_lock);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->number_meal++;
	philo->should_eat--;
	if (philo->should_eat == 0)
		philo->data->is_full++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	my_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks_lock[philo->r_fork]);
	pthread_mutex_unlock(&philo->data->forks_lock[philo->l_fork]);
	print_msg(philo, philo->id, B_BLUE, "is sleeping");
	my_usleep(philo->data->time_to_sleep);
	print_msg(philo, philo->id, BLUE, "is thinking");
}

void	*health_checker(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	my_usleep(philo->data->time_to_die);
	while (i < philo->data->number_philo)
	{
		if (death_checker(&philo[i]))
			return (NULL);
		i++;
	}
	return (NULL);
}

int	death_checker(t_philo *philo)
{
	int		dead;

	dead = 0;
	pthread_mutex_lock(&philo->data->time_lock);
	if (((get_time() - philo->last_meal_time) >= philo->data->time_to_die) && philo->data->is_full < philo->data->number_philo)
	{
		pthread_mutex_unlock(&philo->data->time_lock);
		pthread_mutex_lock(&philo->data->dead_lock);
		philo->data->is_dead = 1;
		philo->data->end_sim = true;
		pthread_mutex_unlock(&philo->data->dead_lock);
		print_msg_death(philo, philo->id, PINK, "is dead");
		dead = 1;
	}
	else 
		pthread_mutex_unlock(&philo->data->time_lock);
	return (dead);
}
