/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:31:28 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/29 13:40:01 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	change_state(t_data *data, t_state state)
{
	pthread_mutex_lock(&data->philo->state_lock);
	if(data->philo->state != DEAD)
		data->philo->state = state;
	pthread_mutex_unlock(&data->philo->state_lock);
}

void	print_msg(t_data *data, int id, msg)
{
	
}