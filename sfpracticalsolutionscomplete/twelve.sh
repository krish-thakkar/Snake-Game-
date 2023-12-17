#!/bin/bash
sort_descending(){
    arr=("$@")
    n=${#arr[@]}
    for ((i = 0;i< n -1;i++)); do
       for((j=0;j<n-i-1;j++)); do
            if ((arr[j] <arr[j+1])); then
                temp=${arr[j]}
                arr[j]=${arr[j+1]}
                arr[j+1]=$temp
            fi
       done
    done
    echo "${arr[@]}"
}
sort_ascending(){
    arr=("$@")
    n=${#arr[@]}
    for ((i=0;i<n-1;i++)); do
       for((j=0;j<n-i-1;j++));do
          if ((arr[j] > arr[j+1])); then
              temp=${arr[j]}
              arr[j]=${arr[j+1]}
              arr[j+1]=$temp
          fi
       done
    done
    echo "${arr[@]}"
}
echo "enter array"
read -a array
if [ "$$" -ne 0 ]; then
    echo "$(sort_descending ${array[@]})"
else 
    wait $$
    echo "$(sort_ascending ${array[@]})"
fi