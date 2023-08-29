echo "Enter a string"
read str

rev=""
l=${#str}

for((i=$l-1 ; i>=0 ; i--))
do
rev="$rev${str:$i:1}"
done
echo $rev
if [ $str == $rev ]
then
echo "palindrome String"
else
echo "not palindrome String"
fi


