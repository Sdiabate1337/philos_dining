/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiabate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:50:12 by sdiabate          #+#    #+#             */
/*   Updated: 2023/12/07 16:52:03 by sdiabate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philosophers.h"

void	init(t_simul *simul, int argc, char **argv)
{
	char_2_int(simul, argc, argv);
	simul->all_ate = 0;
	simul->dead = 0;
	init_mutex(simul);
	init_philos(simul);
}

void	char_2_int(t_simul *simul, int argc, char *argv[])
{
	simul->number_of_philosophers = ft_atoi(argv[1]);
	simul->time_to_die = ft_atoi(argv[2]);
	simul->time_to_eat = ft_atoi(argv[3]);
	simul->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		simul->max_meals = ft_atoi(argv[5]);
	else
		simul->max_meals = -1;
}

void	init_mutex(t_simul *simul)
{
	int	i;
	int	ret;

	i = simul->number_of_philosophers - 1;
	while (i >= 0)
	{
		ret = pthread_mutex_init(&simul->forks[i], NULL);
		if (ret != 0)
			err_msg("forks mutex initialization failed");
		i--;
	}
	ret = pthread_mutex_init(&simul->printing, NULL);
	if (ret != 0)
		err_msg("printing mutex initialization failed");
	ret = pthread_mutex_init(&simul->meal, NULL);
	if (ret != 0)
		err_msg("meal mutex initialization failed");
	ret = pthread_mutex_init(&simul->death, NULL);
	if (ret != 0)
		err_msg("death mutex initialization failed");
}

int	init_philos(t_simul *simul)
{
	int	i;

	i = simul->number_of_philosophers - 1;
	while (i >= 0)
	{
		simul->philosopher[i].id = i + 1;
		simul->philosopher[i].number_of_meals = 0;
		simul->philosopher[i].left_fork_id = i;
		simul->philosopher[i].right_fork_id = (i + 1)
			% simul->number_of_philosophers;
		simul->philosopher[i].last_meal = 0;
		simul->philosopher[i].simul = simul;
		i--;
	}
	return (0);
}
