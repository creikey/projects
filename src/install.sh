#!/bin/bash

if [ "$USER" == "root" ]
then
	echo "USER WAS ROOT"
	to_user=$SUDO_USER
else
	to_user=$USER
fi
exec_path=$(pwd)
bashrc_path="/home/$to_user/.bashrc"

if [ "$1" == "--uninstall" ]
then
	line_numb=$(grep -n "Adds projects executable to path" ~/.bashrc | grep -Eo '^[^:]+')
	other_line_numb=$(($line_numb+1))
	sed -e "$line_numb,${other_line_numb}d" "$bashrc_path" > tmprc && mv tmprc "$bashrc_path"
	exit
fi

is_installed=$(grep 'Adds projects executable to path' "$bashrc_path")
if [ "$is_installed" == "" ]
then
	echo -e -n "Installing...\n"
	echo -e -n "# Adds projects executable to path\n" >> "$bashrc_path"
	echo -e -n "export PATH=$exec_path:\$PATH\n" >> "$bashrc_path"
else
	echo "Is installed"
fi
