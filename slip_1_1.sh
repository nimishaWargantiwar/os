#!/bin/bash

file="address.txt"

while true
do
    echo ""
    echo "1. Search"
    echo "2. Add"
    echo "3. Remove"
    echo "4. Quit"
    read -p "Enter your choice: " ch

    if [ $ch -eq 1 ]; then
        read -p "Enter ID or Name to search: " key
        grep -i "$key" $file || echo "Not found."

    elif [ $ch -eq 2 ]; then
        read -p "Enter ID: " id
        read -p "Enter Name: " name
        read -p "Enter Phone: " phone
        echo "$id;$name;$phone" >> $file
        echo "Added."

    elif [ $ch -eq 3 ]; then
        read -p "Enter ID or Name to remove: " key
        grep -iv "$key" $file > temp && mv temp $file
        echo "Removed (if found)."

    elif [ $ch -eq 4 ]; then
        echo "Goodbye!"
        exit

    else
        echo "Invalid choice."
    fi
done
