/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:51:10 by jocorrea          #+#    #+#             */
/*   Updated: 2023/09/24 18:11:45 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					sig;
	unsigned long long	res;

	i = 0;
	res = 0;
	sig = 1;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sig *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		if (res > __LONG_LONG_MAX__ && sig == 1)
			return (0);
		if (res > __LONG_LONG_MAX__ && sig == -1)
			return (-1);
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (res * sig);
}

static int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	check_input(char **argv)
{
	if (!is_num(argv[1]) || ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (!is_num(argv[2]) || ft_atoi(argv[2]) <= 0)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (!is_num(argv[3]) || ft_atoi(argv[3]) <= 0)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (!is_num(argv[4]) || ft_atoi(argv[4]) <= 0)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && (!is_num(argv[5]) || ft_atoi(argv[5]) <= 0))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}

int	main(int args, char	**argv)
{
	t_program	program;

	if (args != 5 && args != 6)
		return (write(2, "Invalid argument numbers\n", 25));
	if (check_input(argv))
		return (1);
	if (!init_program(&program, argv))
		return (1);
	if (create_threads(&program))
		return (1);
	destroy_all(NULL, &program);
	return (0);
}
