#!/bin/bash

# This script is going to calculate the Fibonacci numbers according to the index
# given by end users.

#Zhicheng Pan, 104639463

#The fibonacci sequence is like below:
# 0,   1, 1, 2, 3, 5,    8, 13, 21, 34, 55,   89, 144, 233，377，610， 
#    987，1597，2584，4181，6765，  10946，17711，28657，46368
function fibonacci() 
{
    #fiboIndex is also a global integer variable
    declare -i fiboIndex 
            fiboIndex=$1      
          
#Both fiboIndex=0 and fiboIndex=1 are the return points of recursion.
#it has to reach these two return points, then the recursion can return and 
#fibonacci() can finally complete.
    if [[ fiboIndex -eq 0 ]]; then
            #echo $fiboIndex
            fiboNumber=fiboNumber+$fiboIndex
            

    elif [[ fiboIndex -eq 1 ]]; then
            #echo $fiboIndex
            fiboNumber=fiboNumber+$fiboIndex
            
    else
            #converting the string value "x" into integer value:  $((x)) 
            #echo $(($fiboIndex-1))
            fibonacci $(($fiboIndex-1)) 
            #echo $(($fiboIndex-2))
            fibonacci $(($fiboIndex-2))
                       
      fi  
    
}



#The script starts from here:

    #Defining a global variable to caculate the fibonacci number
	declare -i fiboNumber=0

    #[[ Comparing Expression ]]: -ne, -ge, -gt... for mathamatic comparing;
    # ==, !=, >, < ...for string comparing
    #filter out the invalid inputs: 
    if [[ $# -ne 1 ]]; then  
        #statements
        echo "Please refer to the usage:"
        echo "usage: fibonacci < integer >"
        exit 1
    #the input must be an integer, and it must be greater than or equal to ZERO.
    elif [[ $1 =~ ^-?[1-9][0-9]*$ || $1 =~ ^0$ ]] && [[ $1 -ge 0 ]]; then
        #invoking the fibonacci function to calculate the fibonacci number
        
        fibonacci $1

        #Both $variable and ${variable} are to get the value from a variable
        #Printing out the caculating result
        echo "-----------------------------------------------------------------------"
        echo "The $1th fibonacci number is: " $fiboNumber        

    else

        echo "Your input has to be an integer number, and it must be greater than or equal to ZERO as well!"
        echo "Please try it again."
        exit 1
        

    fi








