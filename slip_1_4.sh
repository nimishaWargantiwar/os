#!/bin/bash

# --- Test if file exists ---
check_file() {
    read -p "Enter filename: " file
    if [ -e "$file" ]; then
        echo "✅ File exists."
    else
        echo "❌ File does not exist."
    fi
}

# --- Read a file ---
read_file() {
    read -p "Enter filename to read: " file
    if [ -e "$file" ]; then
        echo "📄 Contents of $file:"
        cat "$file"
    else
        echo "❌ File not found."
    fi
}

# --- Delete a file ---
delete_file() {
    read -p "Enter filename to delete: " file
    if [ -e "$file" ]; then
        rm "$file"
        echo "🗑️ $file deleted!"
    else
        echo "❌ File not found."
    fi
}

# --- Display list of files ---
list_files() {
    echo "📂 Files in current directory:"
    ls -p | grep -v /
}

# --- Menu ---
while true
 do
    echo ""
    echo "1. Test if file exists"
    echo "2. Read a file"
    echo "3. Delete a file"
    echo "4. Display list of files"
    echo "5. Quit"
    read -p "Enter your choice: " choice

    if [ "$choice" = "1" ]; then
        check_file
    elif [ "$choice" = "2" ]; then
        read_file
    elif [ "$choice" = "3" ]; then
        delete_file
    elif [ "$choice" = "4" ]; then
        list_files
    elif [ "$choice" = "5" ]; then
        echo "👋 Goodbye!"
        break
    else
        echo "❌ Invalid choice!"
    fi
done
