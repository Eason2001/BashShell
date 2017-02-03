#!/bin/bash

# This script is going to list the names of directories and files separately, 
# and display the total number of directories and files.

#Zhicheng Pan, 104639463


#The script starts from here:

    #defining variables to count the number of directories and files
    declare -i dCount=0
	declare -i fCount=0

if [[ $# -ne 1 ]]; then
        echo "Please refer to the usage:"
        echo "usage: ./listfd.sh <directory_name>"
        exit 1

#if end user's input is not a directory, tips will be shown to them.
elif test -f $1
then
    echo "You input a file name but not a directory, pls reinput and try again!"
    exit 1

#String comparing
elif [[ $1 == "/" ]]
then
     echo "Listing the / directory takes too much time, pls input another directory"
     exit 1

#if end user's input is a directory, the listing process will start
elif test -d $1
then
    #using ls command to list names of directories and files, counting the number
    ls -Rl $1
    dCount=$(ls -Rl $1|grep "^d"|wc -l)
    fCount=$(ls -Rl $1|grep "^-"|wc -l)

    #printing out the caculating result
    echo "-----------------------------------------------------------------------"
    echo "The total number of directories is: " ${dCount}
    echo "The total number of files is: " ${fCount}

else
    echo "The directory doesn't exist, pls input a new one!"
    exit 1
fi




