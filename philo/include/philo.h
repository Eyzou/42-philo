/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:59:07 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/30 20:03:30 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>  // pthread and mutex
# include <stdio.h>    // for printf
# include <stdlib.h>   // for malloc / free
# include <string.h>   // for memset
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // write and usleep

typedef struct s_data t_data;

typedef enum e_state
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3,
	FULL = 4,
	FORK = 5
}					t_state;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				number_meal;
	int				start_time;
	int				last_meal_time;
	int				state;
	int				r_fork;
	int				l_fork;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
	int				number_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	int				start_simulation;
	pthread_mutex_t	*forks_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philo;
}					t_data;

// init
int				prog_init(t_data *data, int argc, char **argv);
int				create_thread(t_data *data);
void			*routine(void *arg);
void 			eat(t_data *data);
int				change_state(t_data *data, int state);
void			print_msg(t_data *data, int state);
int				sleeping(t_data *data);

// utils
long			get_time(void);
void 			my_usleep(long milliseconds);
long			ft_atol(const char *str);
void 			error_msg(char *msg);

#endif