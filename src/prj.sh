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
	if [ "$1" == "-h" ] || [ "$1" == "--help" ]; then
		echo -e -n "Project manager:\n-c | --create - creates a new project file in the directory\n-h | --help - displays this help menu\n"
		return
	fi
	if [ "$1" == "-c" ] || [ "$1" == "--create" ]; then
		echo "Creating projecet file in directory '$(pwd)'..."
		count=`ls -1 *.prj 2>/dev/null | wc -l`	
		if [ $count != 0 ]; then
			echo -e -n "Project file exists! Continue? "
			read -n1 ans
			if [ "$ans" == "n" ]; then
				echo -e -n "\nExiting...\n"
				return
			else
				create_project_file
				return
			fi
		else
			create_project_file
			return
		fi
	fi
	echo "Arg not found"
}
