#!/bin/bash

create_project_file() {
	echo -e -n "Project name: "
	read prj_name
	echo
	echo -e -n "Project description: "
	read prj_desc
	echo
	echo -e -n "Is this project a: \nw - work in progress\nd - finished proect\no - other\nPlease choose: "
	read prj_op_status
	echo
	if [ "$prj_op_status" == "w" ]
	then
		prj_status="work in progress"
	elif [ "$prj_op_status" == "d" ]
	then
		prj_status="finished project"
	elif [ "$prj_op_status" == "o" ]
	then
	echo -e -n "Please specify: "
	read prj_status
	echo
	fi
	echo -e -n "name\n$prj_name\ndescription\n$prj_desc\nstatus\n$prj_status" > "${prj_name}.prj"
	echo -e -n "Finished writing to ${prj_name}.prj"
}

prj() {
	if [ "$1" == "-c" ] || [ "$1" == "--create" ]; then
		echo "Creating projecet file in directory '$(pwd)'..."
		if [ -f "*.prj" ]; then
			echo -e -n "Project file exists! Continue? "
			read -n1 ans
			if [ "$ans" == "n" ]; then
				echo -e -n "\nExiting...\n"
				exit
			else
				create_project_file
				return
			fi
		else
			create_project_file
			return
		fi
	fi
}
