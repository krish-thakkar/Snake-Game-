#!/bin/bash
echo "enter the string"
read string
word=$( wc -w < "$string")
character=$( wc -c < "$string")
line=$(wc -l < "$string")
echo "word:$word"
echo "character:$character"
echo "lines:$line"