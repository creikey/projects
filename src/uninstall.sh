#!/bin/bash

# Uninstalls the command that sources prj.sh

bashrc_path="/home/$USER/.bashrc"

if [ ! -f "$bashrc_path" ]; then
	echo "ERROR: COULDN'T FIND BASHRC"
	exit
fi

echo Uninstalling...

line_numb=$(grep -n "# Sources a bash function file for projects" "$bashrc_path" | grep -Eo '^[^:]+')
echo "Line numb is: $line_numb"
if [ "$line_numb" == "" ]; then
	echo "ERROR: FUNCTION NOT FOUND IN BASHRC"
	exit
fi
other_line_numb=$((line_numb+1))
sed -e "$line_numb,${other_line_numb}d" "$bashrc_path" > tmprc && mv tmprc "$bashrc_path"
echo "Uninstalled successfully!"
exit

