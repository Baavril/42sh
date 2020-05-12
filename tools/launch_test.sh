#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    launch_test.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/01 10:05:56 by abarthel          #+#    #+#              #
#    Updated: 2019/08/01 10:05:56 by abarthel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

function make_test_launch
{
	TESTS_PATH='./tools/'
	tests_array=(${TESTS_PATH}*.test)
	make -j
	for file in "${tests_array[@]}"
	do
		printf "\n\n\e[4m\e[92m"$file"\e[0m\n"
		./42sh < $file
	done
	for file in "${tests_array[@]}"
	do
		printf "\n\n\e[4m\e[36m"$file" (env -i)\e[0m\n"
		env -i LAST=\${LASTLONG2} LASTLONG2=\$LAST TRICK=\~ ./42sh < $file
	done
	#make fclean
}

function direct_launch
{
	42sh_PATH='../'
	tests_array=(*.test)
	make -j -C $42sh_PATH
	for file in "${tests_array[@]}"
	do
		printf "\n\n\e[4m\e[92m"$file"\e[0m\n"
		$42sh_PATH./42sh < $file
	done
	for file in "${tests_array[@]}"
	do
		printf "\n\n\e[4m\e[36m"$file" (env -i)\e[0m\n"
		env -i LAST=\${LASTLONG2} LASTLONG2=\$LAST TRICK=\~ $42sh_PATH./42sh < $file
	done
	#make fclean -C $42sh_PATH
}

if [ -z "$1" ]
then
	direct_launch
else
	make_test_launch
fi
