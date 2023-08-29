echo "Enter the Number"
read n
fact=1
i=1
while [ $i -le $n ]
do
 fact=$((fact*i))
 i=$((i+1))
done
echo "Factorial is:$fact"
