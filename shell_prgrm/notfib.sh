echo "Enter the limit"
read n
a=0
b=1
i=1
if [ $n -ge 6 ]
then 
echo "Terms not in fibonnaci series are:"
fi
while [ $i -le $((n-2)) ]
do
fib=$((a+b))
a=$b
b=$fib
if [ $i -ge 3 ]
then
j=$a
k=$b
while [ $j -lt $((k-1)) ]
do 
echo $((j+1))
j=$((j+1))
done
fi
i=$((i+1))
done
