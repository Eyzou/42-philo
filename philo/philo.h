/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:59:07 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/28 14:28:42 by ehamm            ###   ########.fr       */
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

typedef	s_philo 
{

}	t_philo;

typedef s_fork
{

} t_fork;

typedef	s_data 
{
	int	number_philo;
	int
}	t_data;


#endif 