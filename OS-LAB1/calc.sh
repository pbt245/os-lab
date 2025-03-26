#!/bin/bash

HIST_FILE="calc_history.txt"
ANS=0

touch "$HIST_FILE"

# format_input() {
#     echo "$1" | sed -E 's/([0-9])([-+*/%])([0-9])/\1 \2 \3/g'
# }

calculate() {
  local expr="$1"
  if [[ "$expr" == *"%"* ]]; then
    if [[ ! "$expr" =~ ^-?[0-9]+[[:space:]]*%[[:space:]]*-?[0-9]+$ ]]; then
      echo "SYNTAX ERROR"
      return
    fi

    local num1=$(echo "$expr" | awk '{print $1}')
    local num2=$(echo "$expr" | awk '{print $3}')

    if [[ "$num2" -eq 0 ]]; then
      echo "MATH ERROR"
      return
    fi

    local result=$((num1 % num2))

  else
    local result=$(echo "$expr" | bc -l 2>/dev/null)
  fi

  # check res
  if [[ $? -ne 0 || -z "$result" ]]; then # exit status not equals 0 means error
    echo "SYNTAX ERROR"
    return
  fi

  # 2 floating points
  if [[ "$result" == *.* ]]; then
    result=$(printf "%.2f" "$result")
  fi

  echo "$result"
  ANS="$result"

  # history
  echo "$expr = $result" >>"$HIST_FILE"
  # 5 recent calculations
  tail -n 5 "$HIST_FILE" >"$HIST_FILE.tmp" && mv "$HIST_FILE.tmp" "$HIST_FILE"
}

# loop until exit
while true; do
  echo -n ">> "
  read input

  if [[ "$input" == "EXIT" ]]; then
    break
  fi

  if [[ "$input" == "HIST" ]]; then
    cat "$HIST_FILE"
    continue
  fi

  input=${input//ANS/$ANS}

  calculate "$input"
done
