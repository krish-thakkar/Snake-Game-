#!/bin/bash
echo "enter the number"
read number
temp=0
reverse=0
while ((number!=0)); do
    temp=$((number%10))
    reverse=$((reverse+temp))
    number=$((number/10))
done
echo "$reverse"