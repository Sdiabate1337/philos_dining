/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiabate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:52:11 by sdiabate          #+#    #+#             */
/*   Updated: 2023/12/07 16:53:43 by sdiabate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philosophers.h"

int	main(int argc, char *argv[])
{
	t_simul	simul;

	if (argc < 5 || argc > 6)
		err_msg("Wrong number of arguments");
	if (check_params(argc, argv) == 0)
		err_msg("Wrong parameters");
	init(&simul, argc, argv);
	simulation(&simul);
	return (0);
}

int	check_params(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	if (ft_atoi(argv[1]) < 1)
		return (0);
	else if (ft_atoi(argv[1]) >= 1337)
		err_msg("Too many philosophers");
	else if (ft_atoi(argv[2]) < 0)
		return (0);
	else if (ft_atoi(argv[3]) < 0)
		return (0);
	else if (ft_atoi(argv[4]) < 0)
		return (0);
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (0);
	return (1);
}

void	err_msg(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}
