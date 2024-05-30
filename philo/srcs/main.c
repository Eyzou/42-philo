/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:54:02 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/29 13:36:29 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main (int argc, char **argv)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	prog_init(data,argc,argv);
	create_thread(data);
}