#!/bin/bash
echo "Enter three numbers"
read num1
read num2
read num3
if (((num1>num2) && (num1>num3)));then
     echo "$num1 is greater"
elif (((num2>num1) && ((num2>num3))));then
     echo "$num2 is greater"
elif (((num3>num1) &&(num3>num2)));then
     echo "$num3 is greater"
else
    echo "all numbers are equal"
fi
