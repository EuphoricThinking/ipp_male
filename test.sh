#!/bin/bash

GREEN="\033[0;32m"
RED="\033[0;31m"
BLUE="\033[0;34m"
NOCOL="\033[0m"

function correct_result {
	printf "${GREEN}OK\n${NOCOL}"
}

function wrong_result {
	printf "${RED}WRONG\n${NOCOL}"
}

echo "$#"
echo "$1"
if [ "$#" -ne 2 ]; then
	echo "Too few arguments: ./test.sh program directory"

	exit 1;
fi


for test in $2/*.in; do
	prefix=${test%.in}
	stderr_temp="${test%.in}_temp.err"
	stdout_temp="${test%.in}_temp.out"
	echo -n "$prefix "
#	echo ${test}
	"./$1" < ${test} > ${stdout_temp} 2> ${stderr_temp}
	DIFF_OUT=$(diff ${test%.in}.out ${stdout_temp})
	DIFF_ERR=$(diff ${test%.in}.err ${stderr_temp})

	if [ "$DIFF_OUT" != "" ] || [ "$DIFF_ERR" != "" ]; then
		wrong_result
		if [ "$DIFF_OUT" != "" ]; then
			printf "${RED}Expected out:${NOCOL}\n"
			cat ${test%.in}.out
			printf "${RED}Got:${NOCOL}\n"
			cat ${stdout_temp}
		fi

		if [ "$DIFF_ERR" != "" ]; then
			printf "${RED}Expected err:${NOCOL}\n"
			cat ${test%.in}.err
			printf "${RED}Got:${NOCOL}\n"
                	cat ${stderr_temp}
		fi

		printf "${BLUE}***END*OF*REPORT***${NOCOL}\n\n"
	else
		correct_result
	fi

done

rm $2/*temp*
