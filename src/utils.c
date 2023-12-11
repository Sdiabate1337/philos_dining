/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiabate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:55:56 by sdiabate          #+#    #+#             */
/*   Updated: 2023/12/07 16:56:04 by sdiabate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philosophers.h"

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	t;

	gettimeofday(&time, NULL);
	t = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (t);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			err_msg("Parameter not unsigned int");
		i++;
	}
	i = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb);
}

void	write_death(t_simul *simul)
{
	pthread_mutex_lock(&simul->death);
	simul->dead = 1;
	pthread_mutex_unlock(&simul->death);
}

int	read_death(t_simul *simul)
{
	int	result;

	pthread_mutex_lock(&simul->death);
	result = simul->dead;
	pthread_mutex_unlock(&simul->death);
	return (result);
}

unsigned long	pulse_check(t_simul *simul, int i)
{
	unsigned long	result;

	pthread_mutex_lock(&simul->meal);
	result = get_time() - simul->philosopher[i].last_meal;
	pthread_mutex_unlock(&simul->meal);
	return (result);
}
