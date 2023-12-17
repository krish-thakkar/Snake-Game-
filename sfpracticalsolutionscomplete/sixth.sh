echo "enter the number"
read number
num1=0
num2=1
sum=0
i=0
while ((i<=number));do
      echo $num1
      sum=$((num1+num2))
      temp=$num2
      num2=$sum
      num1=$temp
      ((i++))
done