/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:42:32 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/28 16:05:17 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	prog_init(t_data *data, char **argv)
{
	data_init(data,argv);
	philo_init(data->philo);
	fork_init(data->fork);
}
int data_init(t_data *data, char **argv)
{
	data = malloc(sizeof(t_data));
	data->number_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->time_must_eat = ft_atoi(argv[5]);
	data->number_meal = 0;
}
int	philo_init(t_philo *philo)
{
	philo = malloc(sizeof(t_philo));

}
int	fork_init(t_fork *fork)
{
	fork = malloc(sizeof(t_fork));
	fork->right = 0;
	fork->left = 0;
}

