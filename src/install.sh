#!/bin/bash

# Installs the prj function to bashrc

script_path=$(pwd)

user_dir="/home/$USER"
if [ ! -d "$user_dir" ]; then
	echo "ERROR: NO USER DIRECTORY FOR DIRECTORY $user_dir"
	exit
else
	echo "User directory is $user_dir..."
	echo "Scanning for .project folder!"
	if [ -d "$user_dir/.projects" ]
	then
		echo "PROJECT DIR FOUND! CONTENTS: "
		cd "$user_dir/.projects"
		ls -la
		echo -e -n "Continue? "
		read -n1 ans
		echo
		if [ "$ans" == "n" ]
		then
			exit
		else
			echo "Continuing..."
		fi
	else
		echo "No project dir found!"
		echo "Creating..."
		mkdir "$user_dir/.projects"
	fi
	echo "Copying script file..."
	cp "$script_path/prj.sh" "$user_dir/.projects"
	echo "Creating project data..."
	touch prj_data "$user_dir/.projects"
	echo "Copying uninstall file..."
	cp "$script_path/uninstall.sh" "$user_dir/.projects"
	bash_to_add="# Sources a bash function file for projects\nsource $user_dir/.projects/prj.sh"
	bash_to_check="# Sources a bash function file for projects"
	is_installed=$(grep "$bash_to_check" "$user_dir/.bashrc")
	if [ "$is_installed" == "" ]; then
		echo -e -n "Would you like to add the following lines to the .bashrc file? "
		echo -e -n "\n$bash_to_add\n"
		echo -e -n "? "
		read -n1 ans
		if [ "$ans" == "y" ]; then
			echo -e -n "\n$bash_to_add" >> "$user_dir/.bashrc"
			echo "Written!"
		else
			echo "Cancelling..."
			exit
		fi
	else
		echo "Already added to bashrc"
	fi
fi
