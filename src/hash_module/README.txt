# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    READ_ME.txt                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 15:59:37 by tgouedar          #+#    #+#              #
#    Updated: 2019/10/12 23:24:59 by tgouedar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


HASH TABLE MODULE

#include "hash_module.h"

I.Purpose

This module is meant to be part of the larger 42sh project I worked on with 4
other students of the 42 school.
It allows any subprogram to create, fill, map destroy a hash table.

TO WHOM MIGHT WONDER: Hash tables are data structures that allow users to look
	up for any given data in constant time. They rely on cryptographic hash
	functions to give data a certain index. If the table(/array) is wide enough
	and certain parameters chosen in a smart manner (see load factor, size is a
	prime etc..), complex maths tells us there is a high probability the entry
	will be the only one coupled with the index it was filed at. This module
	takes no chance though, and avoids collision by chaining data with the same.
	The main inconvenient of hash tables is the gigantic memory hog.

It is fully independant and can be called in the shell by invocking functions of
hash_module.h header.

USER BE WARNED, this module DOES NOT keep track of the memory it
allocated ; Any table init'd by ft_init_htable must be free'd with
ft_free_htable lest you want memory leaks!


II.FURTHER EXPLANATION

o> ft_init_htable : entry_nbr is a rough estimate of number of entries you think
	your table will have. It is not critical to nail this number as the module
	keeps track of the load factor and resizes the hash table it gets too
	cluttered ; although it is good to get it right since any operation mapping
	hash tables aren't the most efficient. If you have no idea, you could always
	use DEF_SIZE macro. A hash table for binaries such as those used in shells
	to avoid many system calls when looking for known executables may use
	AVG_BIN_NBR as entry_nbr.

o> ft_insert : needs a htable, a key to hash and the value of the entry. key is
	fed to the cryptogrphic function to determine the index of the entry. value
	is the data of the entry. A use could be, for example key = "grep", value =
	"/usr/bin/grep".

o> ft_get_entry : if key corresponds with an entry of your table, the value of
	this entry (see ft_insert) is returned.

o> ft_hash_path : On the first call, it will find every executable binary in a
	path variable (that must be formatted as they are in a shell environment, 
	i.e. FILE1:FILE2:FILE3) and insert them in the given hash table. It will
	then statically keep track of the last "hashed" path. If it is recalled the
	new path is compared with the one in memory. On a difference, it will empty
	the hash table and re-insert the newly found binaries in the hash table.

o> ft_print_sortentries : Will print each entry on a line the format key=value
	and sorted in ascii values of keys.

o> ft_free_htable : pretty straight foward.


III.ERRORS

The only Error is due to shortage of memory when allocating.
Functions are not protected against any segfault poor designing might cause.


IV.NOTA BENE

This piece of code uses functions that can be found in my libft, which is a
library of standard functions mandatory to any student of 42. Mine was enhanced,
as anyone should have, with a few of my own functions. Thus I recommand using
my lib.
