/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hashing.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dominique <dominique@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/25 18:15:18 by dominique     #+#    #+#                 */
/*   Updated: 2020/04/29 06:26:19 by dominique     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
** Function ft_create_hash_table where we malloc the hash table 
** for a size double than the amount of rooms
** We also initialize the hash table to NULL
*/

t_hash_table		*ft_create_hash_table(unsigned int size)
{
	t_hash_table	*hash_table;
	size_t			i;

	hash_table = (t_hash_table*)ft_memalloc(sizeof(t_hash_table));
	if (hash_table == NULL)
		return (NULL);
	hash_table->size = size * 2;
	hash_table->array = (t_hash_item**)ft_memalloc(sizeof(t_hash_item*) * hash_table->size);
	if (hash_table->array == NULL)
		return (NULL);
	i = 0;
	while (i < hash_table->size)
	{
		hash_table->array[i] = NULL;
		i += 1;
	}
	return (hash_table);
}

/*
** Hash function that will take as input the name of the room
** and will return a key/index in the hash table
** the key should not be negative since it is used for the index
** of the table so we will return an unsigned int
*/

unsigned int		ft_hash_function(char *name, int size)
{
	unsigned int	key;
	size_t			i;
	size_t			len;

	key = 0;
	i = 0;
	len = ft_strlen(name);
	while (i < len)
	{
		key += name[i];
		key = (key * name[i]);
		i += 1;
	}
	key = key % size;
	ft_printf("Room name '%s'\t --> hashed to key -> \t%u\n", name, key);
	return (key);
}

/*
** CAUTION : when create_hash_table returns NULL -> handle it
** For every room we malloc a hash_item (which is an item in the hash_table)
** And then to save the room_name in the hash_item->room_name 
** we need to allocate memory equal to the length of the room name (ft_strdup)
*/

int					ft_hashing_process(t_ant_farm *ant_farm, \
										t_hash_table **hash_table)
{
	unsigned int	key;
	t_hash_item		*ht_item;

	*hash_table = ft_create_hash_table(ant_farm->rooms);
	while (ant_farm->rooms_lst != NULL)
	{
		ht_item = ft_memalloc(sizeof(ht_item));
		if (ht_item == NULL)
			return (-1);
		key = ft_hash_function(ant_farm->rooms_lst->name, (*hash_table)->size);
		ht_item->room_name = ft_strdup(ant_farm->rooms_lst->name);
		ht_item->room = ant_farm->rooms_lst;
		// ht_item->hashed_key = key;
		// ft_printf("hashed_name = %d\n", ht_item->hashed_key);
		(*hash_table)->array[key] = ht_item;
		ant_farm->rooms_lst = ant_farm->rooms_lst->next;
	}
	return (0);
}
