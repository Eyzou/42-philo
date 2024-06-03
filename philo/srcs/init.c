/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:42:32 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/03 14:52:36 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int philo_init(t_data *data);
static int data_init(t_data *data, int argc, char **argv);
static int mutex_init(t_data *data);

int prog_init(t_data *data, int argc, char **argv)
{
	data_init(data, argc, argv);
	philo_init(data);
	mutex_init(data);
	return (0);
}

static int data_init(t_data *data, int argc, char **argv)
{
	data->number_philo = ft_atol(argv[1]);
	data->start_simulation = get_time();
	data->philo = malloc(sizeof(t_philo) * data->number_philo);
	if(!data->philo)
		return (free(data->philo), 1);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->end = 0;
	if (argc == 6)
	{
		data->number_must_eat = ft_atol(argv[5]);
		if (data->number_must_eat < 1)
			return (0);
	}
	if (argc == 5)
	{
		if (data->number_philo < 1)
			return (0);
		data->number_must_eat = -1;
	}
	return (0);
}

static int philo_init(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->number_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].number_meal = 0;
		data->philo[i].last_meal_time = 0;
		if (data->philo[i].id % 2 == 0) // exemple : id:0 - takes r_f i(1) and l_f i+1
		{
			data->philo[i].r_fork = i;
			data->philo[i].l_fork = (i + 1) % data->number_philo;
		}
		else// exemple : id:1 - take the left fork 1(i) - fork contention
		{
			data->philo[i].r_fork = (i + 1) % data->number_philo;
			data->philo[i].l_fork = i;
		}
		data->philo[i].data = data;
	}
	return (0);
}

static int mutex_init(t_data *data)
{
	int i;
	i = 0;
	data->forks_lock = malloc(sizeof(pthread_mutex_t) * data->number_philo);
	if (data->forks_lock == NULL)
		return (free(data->forks_lock), 1);
	while (i < data->number_philo)
	{
		if (pthread_mutex_init(&data->forks_lock[i], NULL))
			return (free(data->forks_lock), 1);
		i++;
	}
	if (pthread_mutex_init(&data->write_lock, NULL))
		return (1);
	if(pthread_mutex_init(&data->dead_lock, NULL))
		return (1);
	if(pthread_mutex_init(&data->meal_lock, NULL))
		return (1);
	return (0);
}

int init_thread(t_data *data)
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