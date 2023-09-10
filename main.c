/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysozen <aysozen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:26:04 by aysozen           #+#    #+#             */
/*   Updated: 2023/08/18 13:39:57 by aysozen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	end_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philo)
	{
		if (table->number_of_philo == 1)
			pthread_detach(table->philos[i].thread);
		pthread_join(table->philos[i].thread, NULL);
	}
	pthread_mutex_destroy(&table->stop_count);
	pthread_mutex_destroy(&table->count_eat);
	pthread_mutex_destroy(&table->eat_last);
	pthread_mutex_destroy(&table->is_die);
	pthread_mutex_destroy(&table->is_print);
	i = 0;
	while (i < table->number_of_philo)
		pthread_mutex_destroy(&table->forks[i++]);
	free (table->forks);
	free (table->philos);
	free (table);
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (ft_control(ac, av) == 0)
		return (1);
	table = parse(ac, av);
	if (table != NULL)
	{
		if (table->number_of_philo > 0)
		{
			start_threads(table);
			end_threads(table);
		}
	}
	return (0);
}
