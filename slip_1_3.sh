#!/bin/bash

file="address.txt"

# --- Add Entry ---
add_entry() {
    read -p "Enter ID: " id
    read -p "Enter Name: " name
    read -p "Enter Phone (10 digits): " phone

    if ! [[ "$id" =~ ^[0-9]+$ ]]; then
        echo "❌ Invalid ID!"
        continue
    fi
    # if ! [[ "$phone" =~ ^[0-9]{10}$ ]]; then
    #     echo "❌ Invalid Phone!"
    #     return
    # fi

    echo "$id:$name:$phone" >> "$file"
    echo "✅ Entry added!"
}

# --- Search Entry ---
search_entry() {
    read -p "Enter ID or Name: " key
    grep -i "$key" "$file" || echo "❌ Not found!"
}

# --- Display All Entries ---
display_all() {
    echo "📒 Address Book:"
    cat "$file"
}

# --- Remove Entry ---
remove_entry() {
    read -p "Enter ID or Name to delete: " key
    grep -iv "$key" "$file" > temp && mv temp "$file"
    echo "🗑️ Entry deleted (if found)!"
}

# --- Edit Entry ---
edit_entry() {
    read -p "Enter ID or Name to edit: " key
    line=$(grep -i "$key" "$file")

    if [ -z "$line" ]; then
        echo "❌ Record not found!"
        return
    fi

    echo "Old record: $line"
    read -p "Enter new ID: " id3

    read -p "Enter new Name: " name
    read -p "Enter new Phone (10 digits): " phone

    if ! [[ "$id3" =~ ^[0-9]+$ ]]; then
        echo "❌ Invalid ID!"
        continue
    fi
    # if ! [[ "$phone" =~ ^[0-9]{10}$ ]]; then
    #     echo "❌ Invalid Phone!"
    #     return
    # fi

    new="$id:$name:$phone"
    sed -i.bak "s|$line|$new|" "$file"
    echo "✅ Entry updated!"
}

# --- Menu ---
while true
do
    echo ""
    echo "1. Add Entry"
    echo "2. Search Entry"
    echo "3. Edit Entry"
    echo "4. Remove Entry"
    echo "5. Display All"
    echo "6. Quit"
    read -p "Enter choice: " ch

    if [ "$ch" = "1" ]; then
        add_entry
    elif [ "$ch" = "2" ]; then
        search_entry
    elif [ "$ch" = "3" ]; then
        edit_entry
    elif [ "$ch" = "4" ]; then
        remove_entry
    elif [ "$ch" = "5" ]; then
        display_all
    elif [ "$ch" = "6" ]; then
        echo "👋 Goodbye!"
        break
    else
        echo "❌ Invalid choice!"
    fi
done
