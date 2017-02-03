#!/bin/bash

# This script is going to replace all occurrences of a word by using another word,  
# and store the new text in a target file.

#Zhicheng Pan, 104639463

#The script starts from here:

#defining an integer variable to count the number of words replaced 
declare -i repCount=0
declare -i textTrue=0

if [[ $# -ne 4 ]]; then
        echo "Please refer to the usage:"
        echo "usage: ./replaceWord.sh <inFile> <word> <repWord> <outFile>"
        exit 1

#if end user's input is not a file, tips will be shown to them.
elif test -d $1
then
    echo "You input a directory but not a file, pls reinput and try again!"
    exit 1

#if end user's input is a real text file, the replacing process will start
elif test -f $1
then
    #if textTrue=0, it is not a real text file
    textTrue=$(file $1 |grep -i "text" |wc -l)
    
    if [[ textTrue -eq 0 ]]; then

        echo "The file you input is not a text file, pls reinput and try again!"
        exit 1    

    else

        #only printing out the words which will be replaced: -n
        sed -n "s/$2/$3/gp" $1  

        #caculating the number of words that will be replaced
        repCount=$(sed -n "s/$2/$3/gp" $1|wc -l)  

        #replacing the words and store the new text to a target file
        sed "s/$2/$3/g" $1 > $4
    
        #printing out the caculating result
        echo "-----------------------------------------------------------------------"
        echo "The number of words that have been replaced is: "${repCount}
        echo "The new file with replaced words:"
        echo $(pwd $4)/$4

    fi


#if end user's input is not a file, tips will be shown to them.
else
    echo "The file is not text file or doesn't exist, pls input a new one!"
    exit 1
fi