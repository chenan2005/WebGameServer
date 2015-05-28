#!/bin/bash
echo -n "new project name: "
read project_name
if [[ -e $project_name ]] 
then
	echo "directory exist!"
	exit
fi
cp new_project $project_name -r
mv $project_name/new_project.vcproj $project_name/$project_name.vcproj
mv $project_name/new_project.h $project_name/$project_name.h
mv $project_name/new_project.cpp $project_name/$project_name.cpp
sed -i "s/new_project/$project_name/g" $project_name/$project_name.vcproj
sed -i "s/new_project/$project_name/g" $project_name/$project_name.h
upper_project_name=$(echo $project_name | tr '[a-z]' '[A-Z]')
sed -i "s/__NEW_PROJECT_H__/__"$upper_project_name"_H__/g" $project_name/$project_name.h
sed -i "s/new_project/$project_name/g" $project_name/$project_name.cpp
