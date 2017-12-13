#!/bin/bash

# Installs the prj function to bashrc

user_dir="/home/$USER"
if [ ! -d "$user_dir" ]; then
	echo "ERROR: NO USER DIRECTORY FOR DIRECTORY $user_dir"
	return
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
			return
		else
			echo "Continuing..."
		fi
	else
		echo "No project dir found!"
		echo "Creating..."
		mkdir "$user_dir/.projects"
	fi
fi
