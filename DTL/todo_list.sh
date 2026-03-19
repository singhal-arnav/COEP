#!/bin/bash

TODO_FILE="todo.txt"
touch "$TODO_FILE"

list_todo() {
    if [[ ! -s $TODO_FILE ]]; then
        echo "No tasks in the list."
    else
        nl -w2 -s'. ' "$TODO_FILE"
    fi
}

add_todo() {
    echo "$1" >> "$TODO_FILE"
    echo "Added: $1"
}

remove_todo() {
    sed -i "${1}d" "$TODO_FILE"
    echo "Removed task #$1"
}

sort_todo() {
    sort -o "$TODO_FILE" "$TODO_FILE"
    echo "Sorted tasks."
}

prepend_todo() {
    echo "$1" | cat - "$TODO_FILE" > temp && mv temp "$TODO_FILE"
    echo "Prepended: $1"
}

append_todo() {
    add_todo "$1"
}

deduplicate_todo() {
    awk '!seen[$0]++' "$TODO_FILE" > temp && mv temp "$TODO_FILE"
    echo "Removed duplicate tasks."
}

while true; do
    echo ""
    echo "===== TODO MENU ====="
    echo "1. List tasks"
    echo "2. Add task"
    echo "3. Remove task"
    echo "4. Sort tasks"
    echo "5. Prepend task"
    echo "6. Append task"
    echo "7. Deduplicate tasks"
    echo "8. Exit"
    echo "======================"
    read -p "Choose an option [1-8]: " choice

    case $choice in
        1) list_todo ;;
        2) read -p "Enter task to add: " task; add_todo "$task" ;;
        3) read -p "Enter task number to remove: " num; remove_todo "$num" ;;
        4) sort_todo ;;
        5) read -p "Enter task to prepend: " task; prepend_todo "$task" ;;
        6) read -p "Enter task to append: " task; append_todo "$task" ;;
        7) deduplicate_todo ;;
        8) echo "Goodbye!"; break ;;
        *) echo "Invalid option. Please try again." ;;
    esac
done

