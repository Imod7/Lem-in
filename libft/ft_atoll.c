/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoll.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 15:34:33 by dominique     #+#    #+#                 */
/*   Updated: 2020/04/29 15:35:25 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static long long	make_num(unsigned char *s, int sign)
{
	long long		num;
	int				len;
	int				units;

	len = 0;
	num = 0;
	while (s[len] != '\0' && s[len] >= 48 && s[len] <= 57)
		len++;
	units = 1;
	while ((len - 1) >= 0)
	{
		num = num + (s[len - 1] - 48) * units;
		units = units * 10;
		len--;
	}
	return (num * sign);
}

long long			ft_atoll(const char *str)
{
	unsigned char	*s;
	int				sign;
	int				i;

	sign = 1;
	i = 0;
	s = (unsigned char *)str;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	while ((s[i] == 43 || s[i] == 45) && (s[i + 1] == 43 || s[i + 1] == 45))
		return (0);
	if (s[i] == 45 && s[i + 1] >= 48 && s[i + 1] <= 57)
	{
		sign = -1;
		i++;
	}
	if (s[i] == 43 && s[i + 1] >= 48 && s[i + 1] <= 57)
		return (make_num(&s[i + 1], sign));
	if (s[i] >= 48 && s[i] <= 57)
		return (make_num(&s[i], sign));
	else
		return (0);
}
