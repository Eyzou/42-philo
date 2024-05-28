/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:59:07 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/28 21:54:25 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h> // write and usleep
# include <stdio.h> // for printf
# include <string.h> // for memset 
# include <stdlib.h> // for malloc / free
# include <sys/time.h> // gettimeofday
# include <pthread.h> // pthread and mutex 

typedef	struct s_philo 
{
	int 	id;
	int		number_meal;
	int 	start_eat_time;
	int 	last_meal_time;
}		t_philo;


typedef	struct s_data 
{
	int			number_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			time_must_eat;
	int			death;
	t_philo		*philo;
	pthread_mutex_t l_fork;
	pthread_mutex_t r_fork;
	pthread_mutex_t write;
	pthread_mutex_t dead;
	pthread_mutex_t meal;
}		t_data;


#endif