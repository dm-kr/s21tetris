#!/bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
BLUE="\033[0;34m"
MAGENTA="\033[0;35m"
CYAN="\033[0;36m"
RESET="\033[0m"

echo ""
grep "Overall" $1/genhtml.log
echo -en "${GREEN}"
grep -P '9[0-9]{1,2}\.[0-9]%' $1/genhtml.log
grep -P '100\.0%' $1/genhtml.log
echo -en "${RESET}"
echo -en "${YELLOW}"
grep -P '8[0-9]\.[0-9]%' $1/genhtml.log
echo -en "${RESET}"
echo -en "${RED}"
grep -P '^[0-7][0-9]\.[0-9]%' $1/genhtml.log
echo -e "${RESET}"
