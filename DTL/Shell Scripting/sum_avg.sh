#!/bin/bash

sum=0
count=0

echo "Enter the numbers one by one. Type 'done' to finish:"

while true; do
    read num
    if [ "$num" == "done" ]; then
        break
    fi
    
    if [[ "$num" =~ ^-?[0-9]+(\.[0-9]+)?$ ]]; then
        sum=$(echo "$sum + $num" | bc)
        ((count++))
    else
        echo "Invalid input, please enter a number or 'done' to finish."
    fi
done

if [ $count -gt 0 ]; then
    avg=$(echo "scale=2; $sum / $count" | bc)
    echo "Sum: $sum"
    echo "Average: $avg"
else
    echo "No valid numbers entered."
fi

