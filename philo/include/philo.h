/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:59:07 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/05 17:40:35 by elo              ###   ########.fr       */
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
# include <stdint.h> // uint64_t
# include <limits.h> // limits

# define RESET "\e[0m"
# define PINK "\e[0;38;5;199m"
# define GREEN "\e[0;32m"
# define BLUE "\e[0;34m"
# define G_BLUE "\e[0;38;5;24m"
# define B_BLUE "\e[1;34m"
# define G_CYAN "\e[0;38;5;44m"

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
	pthread_t		t;
	int				id;
	int				number_meal;
	uint64_t		last_meal_time;
	int 			r_fork;
	int				l_fork;
	struct s_data			*data;
}					t_philo;

typedef struct s_data
{
	int				number_philo;
	uint64_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	long int		start_simulation;
	int				end;
	int				is_dead; // compare with time_to_die
	int				is_full; // compare with number_must_eat
	pthread_mutex_t	*forks_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	end_lock;
	t_philo			*philo;
}					t_data;

// init
int				prog_init(t_data *data, int argc, char **argv);
int				init_thread(t_data *data);
void			*death_checker(void *arg);
void			*routine(void *arg);
void 			eat_sleep_think(t_philo *philo);
int				is_dead(t_philo *philo, int nb);

// utils
size_t			get_time(void);
void 			my_usleep(size_t milliseconds);
long			ft_atol(const char *str);
void 			error_msg(char *msg);
void			print_msg(t_data *data, int id, char *color, char *msg);

#endif