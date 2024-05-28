/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:54:02 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/28 13:46:14 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine(char **argv)
{
	int i;
	i = 0;

}

int create_thread(char **argv)
{
	pthread_t t1;
	int i;
	while(i > ft_atoi(argv[1]))
	{
		pthread_create(&t1, NULL, &routine(argv) ,NULL);
		i++;
	}
	pthread_join(t1,NULL);
	return (0);
}

int main (int argc, char **argv)
{
	pthread_t t1;
	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	create_thread;
	join_thread;
}