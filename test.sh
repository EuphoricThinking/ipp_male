#!/bin/bash

GREEN="\033[0;32m"
RED="\033[0;31m"
NOCOL="\033[0m"

function correct_result {
	printf "${GREEN}OK\n${NOCOL}"
}

function wrong_result {
	printf "${RED}WRONG\n${NOCOL}"
}

function test_args {
	if [ "$#" -ne 2 ]; then
		echo "Too few arguments"

		return 1;
	fi
}

correct_result
wrong_result
test_args
