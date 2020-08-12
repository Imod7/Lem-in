/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_prgm_options.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 14:22:04 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/12 14:22:21 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Function that prints the usage if the option -u is given
** or in case other characters are given that are not valid
** to indicate the way to use the options
*/

static int		ft_print_usage(t_ant_farm *ant_farm, int flag)
{
	if (flag == ERROR)
		ft_printf("--- illegal option(s) were given\n");
	ft_printf("usage: ./lem-in [-u | -m | -a | -l] < path/to/mapfile \n");
	ft_printf("                 -u : prints the usage\n");
	ft_printf("                 -m : ");
	ft_printf("does not display the map data before the ants move\n");
	ft_printf("                 -a : ");
	ft_printf("does not display the lines with the ants moves\n");
	ft_printf("                 -l : ");
	ft_printf("prints the number of lines (required for the moving of ants)\n");
	free(ant_farm);
	return (SUCCESS);
}

/*
** This function sets the prgm options which they can be
** [-u | -vnc]
** It will check the first argument if it starts with the
** minus sign and if the next character is an alphabet.
** If yes, it is an option so it has to be one of the options
** available otherwise it will print the illegal options msg,
** then the usage and then exit the program.
** If all options are valid and the -u is enabled it will print
** the usage and again exit the program.
** In all other cases the program will continue
*/

int				set_prgm_options(char *argv, t_ant_farm *ant_farm)
{
	size_t		i;

	i = 0;
	if (argv[i] == '-')
	{
		i += 1;
		while ((argv[i] != 0) && (ft_isalpha(argv[i]) == 1))
		{
			if (argv[i] == 'u')
				ant_farm->options |= OPTION_U;
			else if (argv[i] == 'm')
				ant_farm->options |= OPTION_M;
			else if (argv[i] == 'a')
				ant_farm->options |= OPTION_A;
			else if (argv[i] == 'l')
				ant_farm->options |= OPTION_L;
			else
				return (ft_print_usage(ant_farm, ERROR));
			i += 1;
		}
	}
	if (ant_farm->options & OPTION_U)
		return (ft_print_usage(ant_farm, SUCCESS));
	return (CONTINUE);
}
