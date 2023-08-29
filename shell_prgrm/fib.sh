echo "Enter the limit"
read n
a=0
b=1
echo $a
echo $b
i=1
while [ $i -le $((n-2)) ]
do
fib=$((a+b))
a=$b
b=$fib
i=$((i+1))
echo "$fib"
done
