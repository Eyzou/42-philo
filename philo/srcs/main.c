/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:40:28 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/11 15:54:34 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	if (prog_init(data, argc, argv) == 1 || init_thread(data) == 1)
		return (EXIT_FAILURE);
	else 
		clean_all(data);
	return (EXIT_SUCCESS);
}
