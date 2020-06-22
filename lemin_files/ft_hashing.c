/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hashing.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 10:38:04 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/06/19 10:48:23 by dsaripap      ########   odam.nl         */
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
** Function that will take as input the name of the room (string)
** and will return a pointer to the correct hash_item where this
** room resides
*/

t_hash_item 		*ft_retrieve_hash_item(t_hash_table *hash_table, char *str)
{
    t_hash_item 	*temp_item;
    unsigned int 	key;

	// ft_printf(" -Looking up the hash_item %s in the hash table\n", str);
	key = ft_hash_function(str, hash_table->size);
	temp_item = hash_table->array[key];
	while (temp_item)
	{
		// ft_printf(" -Comparing room %s with str %s\n", temp_item->room_name, str);
		if (ft_strcmp(str, temp_item->room_name) == 0) 
			return (temp_item);
		temp_item = temp_item->colision_next;
	}
    return (NULL);
}

/*
** Hash function that will take as input the name of the room (string)
** and will return a key/index in the hash table.
** The key should not be negative since it is used for the index
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
	// ft_printf("Room name '%s'\t --> hashed to key -> \t%u\n", name, key);
	return (key);
}

/*
** Function that saves a room in the Hash Table
** For every room we malloc a hash_item (which is an item in the hash_table)
** And then to save the room_name in the hash_item->room_name 
** we need to allocate memory equal to the length of the room name (ft_strdup)
** If the key in th Hash Table is already occupied then we add a node
** in the collision_next linked list
** CAUTION : when create_hash_table returns NULL we handle it
*/

int					ft_hashing_process(t_ant_farm *ant_farm)
{
	unsigned int	key;
	t_hash_item		*ht_item;
	t_hash_item		*temp_item;
	t_room			*temp;

	temp = ant_farm->rooms_lst;
	ant_farm->hash_table = ft_create_hash_table(ant_farm->rooms);
	while (temp != NULL)
	{
		// ft_printf("Room : '%s'\n", temp->name);
		// ht_item = ft_memalloc(sizeof(ht_item));
		if (ht_item == NULL)
			return (-1);
		key = ft_hash_function(temp->name, ant_farm->hash_table->size);
		if (ant_farm->hash_table->array[key] == NULL)
		{
			// ft_printf("Saving room '%s' in key '%d'\n", temp->name, key);
			ht_item = ft_hashitem_newnode(temp);
			ft_hashitem_addend(&(ant_farm->hash_table->array[key]), ht_item);
		}
		else
		{
			// ft_printf(" Key '%d' exists\n", key);
			temp_item = ant_farm->hash_table->array[key];
			while(temp_item->colision_next != NULL)
			{
				// ft_printf(" After item %s of the linkedlist\n", temp_item->room_name);
				temp_item = temp_item->colision_next;
			}
			// ft_printf(" Saving room '%s' in the linked list of key '%d'\n", temp->name, key);
			ht_item = ft_hashitem_newnode(temp);
			ft_hashitem_addend(&(temp_item->colision_next), ht_item);
			}
		temp = temp->next;
		// print_hash_table(ant_farm->hash_table);
	}
	return (0);
}
