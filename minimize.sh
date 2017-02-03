#!/bin/bash

# This script is going to compress files, in the current directory, with some extensions.
# Example: minimize doc jpg txt

#Zhicheng Pan, 104639463



#The script starts from here:

    #Defining a global variable to count the number of files
	declare -i fCount

    #filter out the invalid inputs: 
    if [[ $# -eq 0 ]]; then
        echo "Please refer to the usage:"
        echo "usage: ./minimize.sh < extension list >"
        exit 1

    else

        fCount=0
        for arg in "$@"; do

            echo "-----------------------------------------------------------------------"
            echo "For files with extension: "$arg
            #to obtain the number of files with this extension
            fCount=$(find . -type f -maxdepth 1 -name "*.$arg" |wc -l)

            #If there is not any file with this kind of extension, printing out the excution result
            if [[ fCount -eq 0 ]]; then
            
                echo "There is not any file with extension: "$arg", compression will be ignored."
                echo "-----------------------------------------------------------------------"
            #Or else, create the compressed package, printing out the excution result    
            else
                tar -czvf  $arg.tar.gz  ./*.$arg
                echo  "The compressed package, $arg.tar.gz, has been created successfully,"
                echo  "and it contains $fCount files with $arg extension."
                echo "-----------------------------------------------------------------------"
            fi
            
        done
        

    fi








