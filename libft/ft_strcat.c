/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcat.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/29 16:35:04 by dsaripap      #+#    #+#                 */
/*   Updated: 2019/04/01 17:18:29 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *s1, const char *s2)
{
	int i;
	int s1_len;

	i = 0;
	s1_len = 0;
	while (s1[i] != '\0')
	{
		s1_len++;
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		s1[s1_len] = s2[i];
		i++;
		s1_len++;
	}
	s1[s1_len] = '\0';
	return (s1);
}
