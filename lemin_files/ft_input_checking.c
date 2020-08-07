/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_input_checking.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 15:02:42 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/07 15:52:54 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		add_num(char *str, int sign)
{
	int long long	num;
	int				j;
	int				i;

	num = 0;
	i = 0;
	j = 0;
	while (str[i] != '\0' && (!ft_isdigit(str[i]) || str[i] == '0'))
	{
		if (str[i] == '0')
			j++;
		i++;
	}
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	i -= j;
	num *= sign;
	if (num > 2147483647 || num < -2147483648 || i > 11)
		return (-1);
	return (num);
}

/*
** Function that checks if the given argument
** that corresponds to the room coordinate is valid.
*/

int		check_argv(int *signal, char *str)
{
	int		i;
	int		sign;

	sign = 1;
	i = 0;
	if (!ft_isdigit(str[i]))
		if (str[i] == '-' || str[i] == '+')
		{
			if (str[i] == '-')
				sign = -1;
			if (!ft_isdigit(str[i + 1]))
				return (ERROR);
			i++;
		}
	while (str[i])
		i++;
	i = add_num(str, sign);
	if (i == -1)
		*signal = -10;
	return (i);
}

int				ft_is_number(char *str)
{
	int			i;
	int			sign;
	int			space;

	i = 0;
	sign = 0;
	space = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			space++;
		if ((i == 0) && (str[0] == '+' || str[0] == '-'))
			;
		else if (str[i] < 48 || str[i] > 57 || space > 1)
			return (error_invalid_ants_amount);
		i++;
	}
	return (SUCCESS);
}

/*
** Function that checks if it the format of the line
** that corresponds to the ants amount is valid.
** If the given j is different than 0 it means that
** the number of ants is already set.
*/

int			ft_check_if_ants_amount(t_ant_farm *ant_farm, char *line, size_t j)
{
	ant_farm->signal = CONTINUE;
	// ft_printf("Ants amount : '%s'\n", line);
	if (ant_farm->ants != 0 || ft_is_number(line) != SUCCESS || j != 0)
	{
		return (ft_exit_msg(ant_farm, error_invalid_ants_amount));
	}
	else
	{
		ant_farm->ants = ft_atoi(line);
		// ft_printf(ANSI_COLOR_CYAN"Ants=%d\n"ANSI_COLOR_RESET, ant_farm->ants);
		ant_farm->signal = success_ants_saved;
	}
	return (ant_farm->signal);
}
