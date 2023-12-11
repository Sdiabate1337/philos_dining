/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiabate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:53:53 by sdiabate          #+#    #+#             */
/*   Updated: 2023/12/07 16:55:34 by sdiabate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philosophers.h"

void	simulation(t_simul *simul)
{
	int	i;
	int	ret;

	i = 0;
	simul->start_time = get_time();
	while (i < simul->number_of_philosophers)
	{
		simul->philosopher[i].last_meal = get_time();
		ret = pthread_create(&simul->philosopher[i].thread_id, NULL,
				routine, &(simul->philosopher[i]));
		if (ret != 0)
			exit(EXIT_FAILURE);
		i++;
	}
	death_checker(simul);
	exit_simul(simul);
}

void	*routine(void *params)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)params;
	if (philosopher->id % 2 != 0
		&& philosopher->simul->number_of_philosophers > 1)
		check_and_wait(philosopher->simul->time_to_eat, philosopher);
	while (read_death(philosopher->simul) == 0)
	{
		if (philosopher_eats(philosopher) == 1)
			break ;
		if (philosopher->simul->all_ate != 0
			|| philosopher->number_of_meals == philosopher->simul->max_meals)
			break ;
		print_status(philosopher, "is sleeping");
		check_and_wait(philosopher->simul->time_to_sleep, philosopher);
		print_status(philosopher, "is thinking");
	}
	return (NULL);
}

void	death_checker(t_simul *simul)
{
	int	id;

	while (simul->all_ate == 0)
	{
		id = 0;
		while (id < simul->number_of_philosophers && read_death(simul) == 0)
		{
			if (pulse_check(simul, id) >= (unsigned long)simul->time_to_die)
			{
				if (simul->philosopher[id].number_of_meals != simul->max_meals)
					print_status(simul->philosopher, "died");
				write_death(simul);
			}
			id++;
		}
		if (read_death(simul) != 0)
			break ;
		check_all_philosophers_ate(simul);
	}
}

void	check_all_philosophers_ate(t_simul *simul)
{
	int	i;

	i = 0;
	while (simul->max_meals <= -1 && i < simul->number_of_philosophers
		&& simul->philosopher[i].number_of_meals <= simul->max_meals)
		i++;
	if (i == simul->number_of_philosophers)
		simul->all_ate = 1;
}

void	exit_simul(t_simul *simul)
{
	int	i;

	i = 0;
	while (i < simul->number_of_philosophers)
	{
		pthread_join(simul->philosopher[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < simul->number_of_philosophers)
	{
		pthread_mutex_destroy(&simul->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&simul->printing);
	pthread_mutex_destroy(&simul->meal);
	pthread_mutex_destroy(&simul->death);
}
