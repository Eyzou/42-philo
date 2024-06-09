/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:39:58 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/09 19:52:25 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	eat_sleep_think(t_philo *philo);
//static bool	is_dead(t_philo *philo);

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
		my_usleep(philo->data->time_to_eat);
	while (philo->data->is_dead != 1 && (philo->data->is_full != philo->data->number_philo))
	{
		eat_sleep_think(philo);
		if ((philo->data->is_full == philo->data->number_philo) || philo->data->is_dead == 1)
			return (NULL);
	}
	return (NULL);
}

void	*death_checker(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	my_usleep(philo->data->time_to_die + 20);
			// printf("philo id: %d, get time: %ld last meal time: %ld\n",
			// philo[i].id, get_time(), philo->last_meal_time);
			// printf("get time  - last meal time :%zu \n", (get_time()
			// 		- philo[i].last_meal_time));
			// printf("time to die :%zu \n", philo[i].data->time_to_die);
	while(i < philo->data->number_philo)
	{
		if(is_dead(&philo[i]))
			return(NULL);
		i++;
	}
	return (NULL);
}

static void	eat_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_lock[philo->r_fork]);
	print_msg(philo, philo->id, GREEN, "has taken a r fork");
	pthread_mutex_lock(&philo->data->forks_lock[philo->l_fork]);
	print_msg(philo, philo->id, GREEN, "has taken a l fork");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal_time = get_time();
	philo->number_meal++;
	philo->should_eat--;
	if(philo->should_eat == 0)
		philo->data->is_full++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	print_msg(philo, philo->id, G_CYAN, "is eating");
	my_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks_lock[philo->r_fork]);
	pthread_mutex_unlock(&philo->data->forks_lock[philo->l_fork]);
	print_msg(philo, philo->id, B_BLUE, "is sleeping");
	my_usleep(philo->data->time_to_sleep);
	print_msg(philo, philo->id, BLUE, "is thinking");
}

int	is_dead(t_philo *philo)
{
	int flag;

	flag = 0;
	if ((get_time() - philo->last_meal_time) >= philo->data->time_to_die && philo->data->is_full < philo->data->number_philo)
	{
		print_msg(philo, philo->id, PINK, "is dead");
		pthread_mutex_lock(&philo->data->dead_lock);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		print_msg(philo, philo->id, PINK, "is dead");
		flag = 1;
	}
	return (flag);
}
