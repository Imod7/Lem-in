/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_input_checking.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 15:02:42 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/07 18:43:34 by dsaripap      ########   odam.nl         */
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
** This function calculates the length of the string represented as a number so
** If there is a plus sign in the beginning is NOT added to the length
** If there is a minus sign in the beginning it is added to the length
** If there are leading zeros they are omitted in the calculation of the
** length
*/

static size_t		ft_calculate_length(char *str)
{
	int				i;
	size_t			len;

	i = 0;
	len = 0;
	// ft_printf("str %s \n", str);
	while (str[i] != '\0')
	{
		if (i == 0 && str[i] == '-')
			len += 1;
		else if (i == 0 && str[i] == '+')
			;
		// else if ((i == 0 || i == 1) && str[i] == '0')
		// {
		// 	ft_printf(" str[] %d\n", str[i]);
		// 	while (str[i] == '0')
		// 		i++;
		// 	i--;
		// }
		else if (str[i] >= 48 || str[i] <= 57)
		{
			len += 1;
		}
		i++;
	}
	return (len);
}

/*
** We call first the ft_calculate_length function which
** calculates the length of the string represented as a number.
** Then checks if the length of the string is :
** <= 10 digits if 1st digit is a plus sign
** <= 11 digits if 1st digit is a minus sign
** <= 10 digits if there are no signs in front
*/

static int					ft_check_str_length(char *str)
{
	size_t			len;

	len = ft_calculate_length(str);
	// ft_printf("len %d\n", len);
	if (str[0] == '+' && len > 10)
		return (ERROR);
	else if (str[0] == '-' && len > 11)
		return (ERROR);
	else if (str[0] != '+' && str[0] != '-' && len > 10)
		return (ERROR);
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
	// ft_printf("line : %s j : %d Ants amount : '%d'\n", line, j, ant_farm->ants);
	if (ant_farm->ants != 0 || ft_is_number(line) != SUCCESS || j != 0)
	{
		// ft_printf("--- Ants amount : '%s'\n", line);
		return (ft_exit_msg(ant_farm, error_invalid_ants_amount));
	}
	else
	{
		if (ft_check_str_length(line) == ERROR)
			return (ft_exit_msg(ant_farm, error_invalid_ants_amount));
		ant_farm->ants = ft_atoll(line);
		// ft_printf("____Ants amount : '%lld' \n", ant_farm->ants);
		if (ant_farm->ants <= 0 || ant_farm->ants < -2147483648 || \
		ant_farm->ants > 2147483647)
		{
			// ft_printf("____Ants amount : '%d' \n", ant_farm->ants);
			return (ft_exit_msg(ant_farm, error_invalid_ants_amount));
		}
		// ft_printf(ANSI_COLOR_CYAN"Ants=%d\n"ANSI_COLOR_RESET, ant_farm->ants);
		ant_farm->signal = success_ants_saved;
	}
	return (ant_farm->signal);
}

/*
** Function that checks if we have no links at all
*/

int					ft_check_links(t_ant_farm *ant_farm)
{
	t_hash_item		**hash_item;
	size_t			i;

	hash_item = ant_farm->hash_table->array;
	i = 0;
	while (i < ant_farm->hash_table->size)
	{
		if (hash_item[i] != NULL)
		{
			if (hash_item[i]->room->position == START && \
			hash_item[i]->room->neighbors == NULL)
				return (ft_exit_msg(ant_farm, error_start_room_con));
			if (hash_item[i]->room->position == END && \
			hash_item[i]->room->neighbors == NULL)
				return (ft_exit_msg(ant_farm, error_end_room_con));
			else if (hash_item[i]->room->neighbors != NULL)
			{
				return (SUCCESS);
			}
		}
		i += 1;
	}
	return (ft_exit_msg(ant_farm, error_no_links));
}
