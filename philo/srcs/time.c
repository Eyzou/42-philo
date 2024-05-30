/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:45:48 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/29 13:26:38 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time(void) // return time in milliseconds
{
	struct timeval time;
	if(gettimeofday(&time, NULL) == 1);
		return(1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void my_usleep(long milliseconds)
{
	long start;
	
	start = get_time();
	while((get_time() - start) < milliseconds)
		uspleed(500);
}