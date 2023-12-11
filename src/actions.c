/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiabate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:47:29 by sdiabate          #+#    #+#             */
/*   Updated: 2023/12/07 17:17:20 by sdiabate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philosophers.h"

void	check_and_wait(unsigned long time, t_philosopher *philosopher)
{
	unsigned long	start;

	start = get_time();
	while (read_death(philosopher->simul) == 0)
	{
		if (get_time() - start >= time)
			break ;
		usleep(50);
	}
}

void	print_status(t_philosopher *philosopher, char *str)
{
	pthread_mutex_lock(&philosopher->simul->printing);
	if (read_death(philosopher->simul) == 0)
	{
		printf("%lu ", get_time() - philosopher->simul->start_time);
		printf("%i ", philosopher->id);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&philosopher->simul->printing);
}

int	philosopher_eats(t_philosopher *philo)
{
	if (philo->simul->number_of_philosophers == 1)
	{
		print_status(philo, "has taken a fork");
		return (1);
	}
	pthread_mutex_lock(&philo->simul->forks[philo->left_fork_id]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->simul->forks[philo->right_fork_id]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->simul->meal);
	print_status(philo, "is eating");
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->simul->meal);
	philo->number_of_meals += 1;
	check_and_wait(philo->simul->time_to_eat, philo);
	pthread_mutex_unlock(&philo->simul->forks[philo->right_fork_id]);
	pthread_mutex_unlock(&philo->simul->forks[philo->left_fork_id]);
	return (0);
}
