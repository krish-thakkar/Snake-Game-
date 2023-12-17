#!/bin/bash
echo "Enter a number"
read number
reverse=0
temp=$number
while ((temp>0));do
      reverse=$((reverse * 10 + temp %10))
      temp=$((temp/10))
done
echo "the reverse $reverse"
      