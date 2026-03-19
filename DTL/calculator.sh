#!/bin/bash

evaluate_integer() {
    local expr=$1
    expr=$(echo "$expr" | tr -d ' ')

    while [[ "$expr" =~ \(([^()]+)\) ]]; do
        local sub_expr="${BASH_REMATCH[1]}"
        local sub_result=$(evaluate_integer "$sub_expr")
        expr="${expr/(${sub_expr})/$sub_result}"
    done

    while [[ "$expr" =~ ([0-9]+)([\*/])([0-9]+) ]]; do
        local part="${BASH_REMATCH[0]}"
        local left="${BASH_REMATCH[1]}"
        local op="${BASH_REMATCH[2]}"
        local right="${BASH_REMATCH[3]}"

        local result=0
        if [[ "$op" == "*" ]]; then
            result=$((left * right))
        else
            result=$((left / right))
        fi

        expr="${expr/$part/$result}"
    done

    local result=0
    local op="+"
    local num=""
    while [[ "$expr" =~ ^([-+]?[0-9]+)(.*)$ ]]; do
        num="${BASH_REMATCH[1]}"
        expr="${BASH_REMATCH[2]}"
        case "$op" in
            "+") result=$((result + num)) ;;
            "-") result=$((result - num)) ;;
        esac
        if [[ "$expr" =~ ^([-+]) ]]; then
            op="${BASH_REMATCH[1]}"
            expr="${expr:1}"
        else
            break
        fi
    done

    echo "$result"
}

calculate() {
    local expr=$1
    expr=$(echo "$expr" | tr -d ' ')

    while [[ "$expr" =~ \(([^()]+)\) ]]; do
        local sub_expr="${BASH_REMATCH[1]}"
        local sub_result=$(calculate "$sub_expr")
        expr="${expr/(${sub_expr})/$sub_result}"
    done

    if [[ "$expr" =~ [0-9]+\.[0-9]* ]]; then
        echo "scale=2; $expr" | bc -l
    else
        evaluate_integer "$expr"
    fi
}

last_result=""

while true; do
    if [[ -n "$last_result" ]]; then
        read -e -p "[$last_result] Enter expression (or 'exit' to quit): " input
    else
        read -e -p "Enter expression (or 'exit' to quit): " input
    fi

    if [[ "$input" == "exit" ]]; then
        break
    fi

    if [[ -n "$last_result" ]]; then
        input=${input//Ans/$last_result}
    fi

    if [[ -n "$last_result" && "$input" =~ ^[+-\*/] ]]; then
        input="$last_result $input"
    fi

    last_result=$(calculate "$input")

    if [[ -n "$last_result" ]]; then
        echo "Result: $last_result"
    else
        echo "Invalid input. Try again."
    fi

done

