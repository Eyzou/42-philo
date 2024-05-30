/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:42:32 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/29 13:49:38 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int philo_init(t_data *data);
static int data_init(t_data *data, int argc, char **argv);

int prog_init(t_data *data, int argc, char **argv)
{
	data_init(data, argc, argv);
	philo_init(data);
	mutex_init(data);
	return (0);
}

static int data_init(t_data *data, int argc, char **argv)
{
	data = malloc(sizeof(t_data));
	data->number_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->number_must_eat = ft_atoi(argv[5]);
		if (data->number_must_eat < 1)
			return (0);
	}
	if (argc == 5)
	{
		if (data->number_philo < 1)
			return (0);
		data->number_must_eat = -1;
	}
	// else
	//	data->number_must_eat = INT_MAX;
	return (0);
}

static int philo_init(t_data *data)
{
	t_philo *philo;
	int i;

	philo = data->philo;
	i = -1;
	philo = malloc(sizeof(t_philo) * data->number_philo);
	data->forks = malloc(sizeof(int) * data->number_philo);
	if (philo == NULL || data->forks == NULL)
		return (1);
	while (i++ < data->number_philo)
	{
		data->forks[i] = 0;
		philo[i].id = i + 1;
		philo[i].number_meal = 0;
		philo[i].last_meal_time = get_time();
		philo[i].start_eat_time = 0;
		philo[i].l_fork = i;
		philo[i].r_fork = (i+1) % data->number_philo;
	}
}

static int mutex_init(t_data *data)
{
	int i;
	i = 0;
	data->forks_lock = malloc(sizeof(pthread_mutex_t) * data->number_philo);
	if (data->forks_lock == NULL)
		return (1);
	while(i < data->number_philo)
	{
		pthread_mutex_init(&data->forks_lock[i],NULL);
		i++;
	}
	pthread_mutex_init(&data->write_lock,NULL);
	pthread_mutex_init(&data->dead_lock,NULL);
	pthread_mutex_init(&data->meal_lock,NULL);
	return (0);
}
