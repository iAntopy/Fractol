# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    update_extern_libs.sh                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 17:11:09 by iamongeo          #+#    #+#              #
#    Updated: 2022/08/03 18:13:47 by iamongeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CURR_PATH=$(dirname "$(readlink -f "$0")")

if [ $(uname) = 'Linux' ]
then
	MINILIBX_PATH='../../minilibx/minilibx-linux'
elif [ $(uname) = 'Darwin' ]
then
	MINILIBX_PATH='../../minilibx/minilibx_macos'
else
	MINILIBX_PATH='.'
	echo "Unsuported OS"
fi

LIBFT_PATH='../../libft'
MLXADDS_PATH='../../Zoobag_Renderer/mlx_addons'

if [ $1 = "re" ]; then
	echo "REMOVING ALL LIB LINKS"
	rm lib*.a
else
	echo "DO NOT REMOVE LIB LINK PRESENT"

fi

if [ -d $MINILIBX_PATH -a -f $MINILIBX_PATH'/libmlx.a' ]; then
	echo "creating libmlx.a link"
	ln $MINILIBX_PATH'/libmlx.a' $CURR_PATH'/libmlx.a'
else
	echo "Missing minilibx library"
fi

ls "${CURR_PATH}/${MLXADDS_PATH}" 
if [ -d $MLXADDS_PATH -a -f $MLXADDS_PATH'/libmlxadds.a' ]; then
	echo "creating libmlxadds.a link"
	ln $MLXADDS_PATH"/libmlxadds.a" $CURR_PATH'/libmlxadds.a'
else
	echo "Missing mlx_addons library"
fi

if [ -d $LIBFT_PATH -a -f $LIBFT_PATH"/libft.a" ]; then
	echo "creating libft.a link"
	ln $LIBFT_PATH"/libft.a" $CURR_PATH'/libft.a'
else
	echo "Missing libft library"
fi
