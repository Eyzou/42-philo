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

#include "philo.h"

static int	philo_init(t_philo *philo);
static int data_init(t_data *data, char **argv);

int	prog_init(t_data *data, char **argv)
{
	data_init(data,argv);
	philo_init(data->philo);
}
static int data_init(t_data *data, int argc,char **argv)
{
	data = malloc(sizeof(t_data));
	data->number_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if(argc == 6)
		data->time_must_eat = ft_atoi(argv[5]);
	else
		data->time_must_eat = INT_MAX;

}
static int	philo_init(t_data *data)
{
	t_philo *philo;
	int i;

	philo = data->philo;
	i = 0;
	philo = malloc(sizeof(t_philo) * data->number_philo);
	if (philo == NULL)
		return(NULL);
	while(i < data->number_philo)
	{
		philo[i].id = i + 1;
		philo[i].number_meal = 0 ;
		
	}
	philo->last_meal_time = get_time();
	philo->r_fork = pthread_mutex_init(&data->);
	philo->l_fork = pthread_mutex_init();

}


