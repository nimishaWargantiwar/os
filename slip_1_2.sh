#!/bin/bash

file="phonebook.txt"

while true
do
    echo ""
    echo "---- PHONE BOOK ----"
    echo "1. Add New Entry"
    echo "2. Search Entry"
    echo "3. Sort by Last Name"
    echo "4. Delete Entry"
    echo "5. Quit"
    read -p "Enter your choice: " ch

    if [ "$ch" = "1" ]; then
        # Add Entry
        read -p "Enter First Name: " fname
        if ! [[ "$fname" =~ ^[A-Za-z]+$ ]]; then
            echo "❌ Invalid first name. Use only letters."
            continue
        fi

        read -p "Enter Last Name: " lname
        if ! [[ "$lname" =~ ^[A-Za-z]+$ ]]; then
            echo "❌ Invalid last name. Use only letters."
            continue
        fi

        read -p "Enter Phone (10 digits): " phone
        if ! [[ "$phone" =~ ^[0-9]{10}$ ]]; then
            echo "❌ Invalid phone. Must be 10 digits."
            continue
        fi

        echo -e "$fname\t$lname\t$phone" >> "$file"
        echo "✅ Entry saved!"

    elif [ "$ch" = "2" ]; then
        # Search Entry
        read -p "Enter name or phone to search: " key
        grep -i "$key" "$file" || echo "No match found."

    elif [ "$ch" = "3" ]; then
        # Sort by Last Name (2nd field)
        sort -k2 "$file" -o "$file"
        echo "✅ Sorted by last name."
        cat "$file"

    elif [ "$ch" = "4" ]; then
        # Delete Entry
        read -p "Enter name or phone to delete: " key
        grep -iv "$key" "$file" > temp && mv temp "$file"
        echo "✅ Entry deleted (if found)."

    elif [ "$ch" = "5" ]; then
        echo "👋 Goodbye!"
        break

    else
        echo "❌ Invalid choice!"
    fi
done
