/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:31:28 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/30 18:58:40 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	change_state(t_data *data, int state)
{
	data->philo->state = state;
	if(data->philo->state != DEAD)
		return(state);
	else
		return (DEAD);
}

void	print_msg(t_data *data)
{
	pthread_mutex_lock(&data->write_lock);
	pthread_mutex_unlock(&data->write_lock);
}