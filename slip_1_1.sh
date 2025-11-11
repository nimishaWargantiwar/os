#!/bin/bash

file="address.txt"

while true
do
    echo ""
    echo "1. Search"
    echo "2. Add"
    echo "3. Remove"
    echo "4. Quit"
    read -p "Choice: " ch

    if [ "$ch" = "1" ]; then
        read -p "Enter name or ID: " key
        grep -i "$key" "$file" || echo "Not found."

    elif [ "$ch" = "2" ]; then
        # --- ID validation ---
        read -p "Enter ID (numbers only): " id
        if ! [[ "$id" =~ ^[0-9]+$ ]] ; then
            echo "❌ Invalid ID. Use only numbers."
            continue
        fi

        # --- Name validation ---
        read -p "Enter Name (letters only): " name
        if ! [[ "$name" =~ ^[A-Za-z]+$ ]]; then
            echo "❌ Invalid Name. Use only letters."
            continue
        fi

        # --- Phone validation ---
        read -p "Enter Phone (10 digits): " phone
        if ! [[ "$phone" =~ ^[0-9]{10}$ ]]; then
            echo "❌ Invalid Phone. Must be 10 digits."
            continue
        fi

        echo "$id;$name;$phone" >> "$file"
        echo "✅ Saved successfully!"

    elif [ "$ch" = "3" ]; then
        read -p "Enter name or ID to delete: " key
        grep -iv "$key" "$file" > tmp && mv tmp "$file"
        echo "Deleted (if found)."

    elif [ "$ch" = "4" ]; then
        echo "👋 Bye!"
        break

    else
        echo "Invalid choice!"
    fi
done
