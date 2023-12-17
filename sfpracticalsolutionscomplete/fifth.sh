echo "enter the number"
read primenumber
i=2
result=0
flag=0
while ((i<primenumber));do
     result=$((primenumber%i))
     if ((result == 0));then
         flag=1
         break
    else
        flag=0
    fi
      ((i++))  
done
if ((flag == 1));then
    echo "$primenumber is not a prime"
else
   echo "$primenumber is a prime"
fi