echo "Enter the limit"
read n

for ((i = 2; i <= n; i++))
do
    is_prime=true
    
    for ((j = 2; j <= i/2; j++))
    do
        if [ $((i % j)) -eq 0 ]
        then
            is_prime=false
            break
        fi
    done
    
    if [ "$is_prime" = false ]
    then
        echo "$i"
    fi
done

