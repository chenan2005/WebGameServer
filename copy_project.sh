#!/bin/bash
echo -n "copy from: "
read src_project_name
echo -n "new project name: "
read project_name

if [[ ! -d $src_project_name ]]
then
	echo "source project not exist!"
	read -n1 -p "Press any key to continue..."
	exit
fi

if [[ -e $project_name ]] 
then
	echo "target directory exist!"
	read -n1 -p "Press any key to continue..."
	exit
fi

cp $src_project_name $project_name -r
[[ -e $project_name/Debug ]] && rm $project_name/Debug -r -f
[[ -e $project_name/debug ]] && rm $project_name/debug -r -f
for filename in $(find $project_name/ -name '*.user'); do rm $filename -f; done
mv $project_name/$src_project_name.vcproj $project_name/$project_name.vcproj
mv $project_name/$src_project_name.h $project_name/$project_name.h
mv $project_name/$src_project_name.cpp $project_name/$project_name.cpp
sed -i "s/$src_project_name/$project_name/g" $project_name/$project_name.vcproj
sed -i "s/$src_project_name/$project_name/g" $project_name/$project_name.h
sed -i "s/$src_project_name/$project_name/g" $project_name/$project_name.cpp
upper_src_project_name=$(echo $src_project_name | tr '[a-z]' '[A-Z]')
upper_project_name=$(echo $project_name | tr '[a-z]' '[A-Z]')
sed -i "s/__"$upper_src_project_name"_H__/__"$upper_project_name"_H__/g" $project_name/$project_name.h

#find $project_name/ -type f | grep "^$project_name/$src_project_name" | grep -v "^$project_name/$project_name\."
for filename in $(find $project_name/ -type f | grep "^$project_name/$src_project_name" | grep -v "^$project_name/$project_name\."); do
	sed -i "s/$src_project_name/$project_name/g" $filename
	mv $filename $(echo $filename | sed "s/\/$src_project_name/\/$project_name/g")
done

echo "done"
read -n1 -p "Press any key to continue..."