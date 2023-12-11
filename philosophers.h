/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiabate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:46:01 by sdiabate          #+#    #+#             */
/*   Updated: 2023/12/07 16:46:27 by sdiabate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philosopher
{
	int				id;
	int				left_fork_id;
	int				right_fork_id;
	int				number_of_meals;
	unsigned long	last_meal;
	struct s_simul	*simul;
	pthread_t		thread_id;
}	t_philosopher;

typedef struct s_simul
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				all_ate;
	int				max_meals;
	int				dead;
	t_philosopher	philosopher[1337];
	unsigned long	start_time;
	pthread_mutex_t	meal;
	pthread_mutex_t	printing;
	pthread_mutex_t	death;
	pthread_mutex_t	forks[1337];
}	t_simul;

void			err_msg(char *str);
unsigned long	get_time(void);
int				check_params(int argc, char **argv);

void			check_and_wait(unsigned long time, t_philosopher *philosopher);
void			print_status(t_philosopher *philosopher, char *str);
int				philosopher_eats(t_philosopher *philosopher);

void			init(t_simul *simul, int argc, char **argv);
void			simulation(t_simul *simul);
//void			*pthread(void *params);
void			death_checker(t_simul *simul);
void			check_all_philosophers_ate(t_simul *simul);
void			exit_simul(t_simul *simul);

int				ft_atoi(const char *str);

void			char_2_int(t_simul *simul, int argc, char **argv);
void			init_mutex(t_simul *simul);
int				init_philos(t_simul *simul);

void			*routine(void *params);
int				read_death(t_simul *simul);
void			write_death(t_simul *simul);
unsigned long	pulse_check(t_simul *simul, int i);

#endif
