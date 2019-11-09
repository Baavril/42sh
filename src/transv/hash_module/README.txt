# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    READ_ME.txt                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 15:59:37 by tgouedar          #+#    #+#              #
#    Updated: 2019/10/30 14:48:32 by tgouedar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


HASH TABLE MODULE

#include "hash_module.h"

I.Purpose

This module is meant to be part of the larger 42sh project I worked on with 4
other students of the 42 school.
It allows any subprogram to create, fill, map and destroy a hash table.

TO WHOM MIGHT WONDER: Hash tables are data structures that allow users to look
	up for any given data in constant time. They rely on cryptographic hash
	functions to give data a certain index. If the table(/array) is wide enough
	and certain parameters chosen in a smart manner (see load factor, size is a
	prime etc..), complex maths tells us there is a high probability the entry
	will be the only one coupled with the index it was filed at. This module
	takes no chance though, and avoids collision by chaining data with the same.
	The main inconvenient of hash tables is the gigantic memory hog.

It is fully independant and can be called in a program by invocking functions of
hash_module.h header. It was concieved first and foremost to implement binary
hash builtin of shells. This influence may be percieved throughout the module.

USER BE WARNED: This module DOES NOT keep track of the memory it allocated !!!
Any table init'd by ft_init_htable must be free'd with ft_free_htable lest you
want memory leaks!


II.FURTHER EXPLANATION

This section explains the usable functions of the module: the functions listed
in the hash_module.h header and that are to be called outside of the module.

o> ft_init_htable : Sets up the "memory hog" and stores a set of functions that
	treats the data structure of the entries the user wishes.
	o> entry_nbr: is a rough estimate of number of entries you think your table
		will have. It is not critical to nail this number as the module
		keeps track of the load factor and resizes the hash table it gets too 
		cluttered ; although it is good to get it right since any operation
		mapping hash tables aren't the most efficient. If you have no idea, you
		could always use DEF_SIZE macro. A hash table for binaries such as those
		used in shells to avoid many system calls when looking for known
		executables may use AVG_BIN_NBR as entry_nbr.
	o> data_type : is an int that will allow the module to load the routines
		that treat your data structures. It needs to be a value of the
		e_htable_type that is described in htable_type_dispatcher.h !!! (See
		section III.).

o> ft_insert : Needs a htable, a key to hash and the value of the entry. The key
	is always treated as a string, whereas value is (void*) type so that users
	may insert whatever struct one wishes. However, giving a hash table a
	structure that isn't native to this module requires the user to write a set
	of routines to handle the data type (see section III.).
	When you give the module an entry, it will allocate the elements within the
	structure according to the copy routine you wrote.
	The simplest data one could insert is a string.
	o> key : will be fed to the cryptographic function to determine the index 
		of the entry.
	o> value : is the data of the entry.
		A use could be, for example key = "grep", value = "/usr/bin/grep" (here,
		string entries are used).

o> ft_get_entry : If key corresponds with an entry of your table, the value of
	this entry (see ft_insert) is returned.

o> ft_print_sortentries : Will print each entry on a line in the format that is
	defined in the table's set of behaviours of the table you have defined (see
	section III.).
	key=value sorted in ascii values of keys may be a default behaviour.

o> ft_free_htable : pretty straight foward.

o> ft_hash_path : This function reproduces the zsh hash builtin way of parsing
	PATH for binaries' paths. It will thus works with string entries hash
	tables. On the first call, it will find every executable binary in a path
	variable (that must be formatted as they are in a shell environment,
	i.e. FILE1:FILE2:FILE3) and insert them in the given hash table. It will
	then keep track of the last "hashed" path in  a static variable. If it is
	recalled the new path is compared with the one in memory. On a difference,
	it will empty the hash table and re-insert the newly found binaries in the
	hash table. A call with a NULL path will allow the function to clear the
	dupped path in the static variable from previous calls.


III.USER CUSTOMISATION

This section explains the htable_type_dispatcher.c file you might want to
tinker with.

As previously mentionned, users can keep any type of structure in their htables
for specific needs (bash binary hash table needs to keep track of the number of
times an executable binary has been called). Therefore the module needs to know
how each data type behaves in order to manage the table.
Sets of behaviours are thus preset in the htable_type_dispatcher.c file

Users may choose between zsh hash builtin behaviour or bash hash builtin
behaviour which both are native to this module. However, if a user wishes to
utilize a data structure of his own, this module needs routines throughout its
execution that comply with the structure that is used, such as the way to copy
the data or the way to print it. For any use of a value structure that isn't
native to this module, the user must write a set of functions and put their
addresses in a line of the dispatcher in htable_type_dispatcher.c. It also needs
the size of the structure it must treat, which is the last field of a dispatcher
line.

/!\ Setting behaviour is done at initialisation /!\
The index in the dispatcher of the line you add and/or want to use must also be
the data_type argument of ft_init_htable. We recommand you use the enum defined
in the header matching this file.


IV.ERRORS

The only Error is due to shortage of memory when allocating.
Functions are not protected against any segfault poor designing might cause.


V.NOTA BENE

This piece of code uses functions that can be found in my libft, which is a
library of standard functions mandatory to any student of 42. Mine was enhanced,
as anyone should have, with a few of my own functions. Thus I recommand using
my lib.
