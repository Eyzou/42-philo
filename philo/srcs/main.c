/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:54:02 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/30 18:51:46 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main (int argc, char **argv)
{
	t_data *data;

if(argc == 5 || argc == 6)
{
	data = malloc(sizeof(t_data));
	// pars the input
	prog_init(data,argc,argv);
	create_thread(data);
	// Clean when philos are full or one philo dies
}
else
	error_msg("Error: Wrong number of arguments\n");
}