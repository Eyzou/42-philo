/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:59:07 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/28 16:05:13 by ehamm            ###   ########.fr       */
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
	int	is_full;
}		t_philo;

typedef struct s_fork
{
	int		left;
	int		right;
}		t_fork;

typedef	struct s_data 
{
	int		number_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		time_must_eat;
	int		number_meal;
	t_fork	*fork;
	t_philo	*philo;
}		t_data;


#endif