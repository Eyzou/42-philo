/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:59:07 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/07 10:11:57 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>  // pthread and mutex
# include <stdbool.h>  // booleen
# include <stdio.h>    // for printf
# include <stdlib.h>   // for malloc / free
# include <string.h>   // for memset
# include <sys/time.h> // gettimeofday
# include <stdint.h> // gettimeofday
# include <unistd.h>   // write and usleep
# include <stdint.h> // uint64_t

# define RESET "\e[0m"
# define PINK "\e[0;38;5;199m"
# define GREEN "\e[0;32m"
# define BLUE "\e[0;34m"
# define G_BLUE "\e[0;38;5;24m"
# define B_BLUE "\e[1;34m"
# define G_CYAN "\e[0;38;5;44m"

# define INT_MAX 2147483647

typedef struct s_data	t_data;

typedef enum e_state
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3,
	FULL = 4,
	FORK = 5
}						t_state;

typedef struct s_philo
{
	pthread_t			t;
	int					id;
	int					number_meal;
	size_t			last_meal_time;
	int					r_fork;
	int					l_fork;
	int					is_full;
	struct s_data		*data;
}						t_philo;

typedef struct s_data
{
	int					number_philo;
	size_t			time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_must_eat;
	long int			start_simulation;
	int					is_dead; // compare with time_to_die
	int					is_full; // compare with number_must_eat
	int					end;
	pthread_mutex_t		*forks_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		end_lock;
	t_philo				*philo;
}						t_data;

// init
int			prog_init(t_data *data, int argc, char **argv);
int			init_thread(t_data *data);

// routine
void		*death_checker(void *arg);
void		*routine(void *arg);

// utils
size_t		get_time(void);
void		my_usleep(size_t milliseconds);
long		ft_atol(const char *str);
void			print_msg(t_data *data, int id, char *color, char *msg);

// clean and close
int	error_msg(char *msg);
void		clean_all(t_data *data);

#endif