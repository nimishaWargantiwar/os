#!/bin/bash

file="phonebook.txt"

while true
do
    echo ""
    echo "1. Add Entry"
    echo "2. Search Entry"
    echo "3. Sort by Last Name"
    echo "4. Delete Entry"
    echo "5. Quit"
    read -p "Enter choice: " ch

    if [ "$ch" -eq 1 ]; then
        echo "Enter First Name: "
        read fname
        echo "Enter Last Name: "
        read lname
        echo "Enter Phone Number: "
        read phone
        echo -e "$fname\t$lname\t$phone" >> $file
        echo "Saved!"

    elif [ "$ch" -eq 2 ]; then
        echo "Enter name or phone to search: "
        read key
        grep -i "$key" $file

    elif [ "$ch" -eq 3 ]; then
        sort -k2 $file -o $file
        echo "Sorted by Last Name:"
        cat $file

    elif [ "$ch" -eq 4 ]; then
        echo "Enter name or phone to delete: "
        read key
        grep -iv "$key" $file > temp.txt && mv temp.txt $file
        echo "Deleted (if found)!"

    elif [ "$ch" -eq 5 ]; then
        echo "Bye!"
        break

    else
        echo "Invalid choice!"
    fi
done
