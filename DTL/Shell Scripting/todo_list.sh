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

case "$1" in
    list) list_todo ;;
    add) shift; add_todo "$*" ;;
    remove) remove_todo "$2" ;;
    sort) sort_todo ;;
    prepend) shift; prepend_todo "$*" ;;
    append) shift; append_todo "$*" ;;
    deduplicate) deduplicate_todo ;;
    *) echo "Usage: $0 {list|add|remove <num>|sort|prepend <task>|append <task>|deduplicate}" ;;
esac

