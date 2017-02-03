#!/bin/bash

# This script is going to list all regular files in the current directory that 
# are smaller than n bytes (n is an integer argument).

#Zhicheng Pan, 104639463

#The script starts from here:

#defing a variable to count the number of files that are smaller than n bytes
declare -i fCount=0

if [[ $# -ne 2 ]]; then
        echo "Please refer to the usage:"
        echo "usage: ./listfs.sh <directory_name> <n bytes>"
        exit 1

#if end user's input is not a directory, tips will be shown to them.
elif test -f $1
then
    echo "You input a file name but not a directory, pls reinput and try again!"
    exit 1

#if end user's input is a directory, the finding process will start
elif test -d $1
then
    #The n must be an integer and equal to or greater than ZERO
    if [[ $2 =~ ^-?[1-9][0-9]*$ || $2 =~ ^0$ ]] && [[ $2 -ge 0 ]]; then
    
        #using find command to look for files, wc command to count the number
        find $1 -type f -size -$2c
        fCount=$(find $1 -type f -size -$2c|wc -l)

        #echo -e "\n"
        #printing out the caculating result
        echo "-----------------------------------------------------------------------"
        echo "The total number of files that are smaller than "$2 "bytes is: " ${fCount}

    else

        echo "The n must be an integer and equal to or greater than ZERO, pls input a new one!"
        exit 1    


    fi

else
    echo "The directory doesn't exist, pls input a new one!"
    exit 1
fi

