/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:54:02 by ehamm             #+#    #+#             */
/*   Updated: 2024/06/04 11:08:38 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
	t_data *data;

	if (argc == 5 || argc == 6)
	{
		data = malloc(sizeof(t_data));
		prog_init(data, argc, argv);
		init_thread(data);
		// Clean when philos are full or one philo dies
	}
	else
		error_msg("Error: Wrong number of arguments\n");
}
