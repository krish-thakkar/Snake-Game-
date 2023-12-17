#!/bin/bash

echo "Enter a sentence"
read sentence

count_vowels() {
    echo "$1" | tr -cd 'aeiouAEIOU' | wc -c
}


if [ "$pid" -eq 1 ]; then
    echo "$(echo "$sentence" | wc -w)"
else
    wait $pid
    echo "$(count_vowels "$sentence")"
fi
