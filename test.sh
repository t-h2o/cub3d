#!/bin/sh
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/23 16:51:30 by melogr@phy        #+#    #+#              #
#    Updated: 2022/07/23 16:58:23 by melogr@phy       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# 1. message
msg_green () {
	printf '\e[0;32m%s\n\e[0m' "$1"
}

# 1. message
msg_red () {
	printf '\e[0;31m%s\n\e[0m' "$1"
}

# 1. Comment
# 2. Argument
test_error () {

	printf "# %s\n" "$1"
	printf "./cub3d %s\n" "$2"

	if ! ./cub3d $2;
	then
		msg_green "cub3d found the error: OK!"
	else
		msg_red "cub3d didn't find the error: KO :/"
		exit 1
	fi; echo

}

# Test map with error inside
test_map_error () {

	printf "### Test map with error\n"

	test_error "File do no exist" "nomap.cub"
	test_error "Invalid map extension" "invalid_map"

}

test_norm () {

	printf "### Norminette\n"

	if norminette headers srcs > /dev/null;
	then
		msg_green "Norminette: OK!"
	else
		msg_red "Norminette: KO :/"
		exit 1
	fi

}

makere () {

	if make re;
	then
		msg_green "Compilation OK!"
	else
		exit 1
		msg_red "Error of compilation"
	fi

}


# Main
main () {

	makere
	test_map_error
	test_norm

}

main 
msg_green "TEST SUCCESS"
