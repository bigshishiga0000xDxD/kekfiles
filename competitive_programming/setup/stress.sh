#!/bin/bash

helpmessage="Usage: ./stress.sh -m [MODE] -t [TIMEOUT] -n

-m                Available modes:
                  regular - script will check whether output of
                  main.cpp and dumb.cpp are equal.
                  This requires:
                  1. main.cpp - incorrect, but effective solution.
                  2. dumb.cpp - correct, but ineffective solution.
                  3. generate.cpp - program that generates input.
                  NOTE: all programs should read from stdin and 
                  write to stdout.

                  check - script will check whether return code of
                  check.cpp is zero.
                  This requires:
                  1. main.cpp - incorrect solution.
                  2. generate.cpp - program that generates input.
                  3. check.cpp - program that checks whether output
                  is correct.
                  NOTE: check.cpp should manually read from files
                  input.txt and output.txt.

                  'regular' by default.

-t                Number of seconds that script should be running.

                  Infinity by defalut.
"

mode="regular"
t="9999999999"

while getopts ":h:m:t:" opt; do
    case $opt in
        h)
            echo "$helpmessage" >&2
            exit 0
            ;;
        m)
            mode=$OPTARG
            if [ "$mode" != "regular" ] && [ "$mode" != "check" ]
            then
                echo "Invalid mode: $mode" >&2
                exit 1
            fi
            ;;
        t)
            t=$OPTARG
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            exit 1
            ;;
        :)
            if [ "$OPTARG" == "h" ]
            then
                echo "$helpmessage" >&2
                exit 0
            else
                echo "Option -$OPTARG requires an argument." >&2
                exit 1
            fi
            ;;
    esac
done

t+="s"

if [[ "$mode" == "check" ]]
then
    trap 'rm -f main.out generate.out check.out; exit 2' INT
    touch Stress

    echo "compiling..."
    echo "all: main generate check

main.o: main.cpp
	g++ -w -c main.cpp -o main.o
generate.o: generate.cpp
	g++ -w -c generate.cpp -o generate.o
check.o: check.cpp
	g++ -w -c check.cpp -o check.o

main: main.o
	g++ main.o -o main.out
generate: generate.o
	g++ generate.o -o generate.out
check: check.o
	g++ check.o -o check.out" > Stress

    make -s -f Stress
    if [[ "$?" == "2" ]]
    then
        echo "compilation failed"
        exit 2
    fi

    function runCheck {
        it=1

        while (true)
        do
            ./generate.out > input.txt
            ./main.out < input.txt > output.txt
            ./check.out
            if [ "$?" == "0" ]
            then
                ((it=it+1))
                echo -en "\riteration $it"
            else
                echo "error found after $it iterations. check out input.txt and output.txt"
                break
            fi
        done
    }

    export -f runCheck

    echo "starting ..."
    timeout --foreground "$t" bash -c runCheck

    if [ "$?" == "124" ]
    then
        echo "error not found"
    fi
    
    rm generate.out main.out check.out
else
    trap 'rm -f main.out dumb.out generate.out; exit 2' INT
    touch Stress

    echo "compiling ..."
    echo "all: main dumb generate

main.o: main.cpp
	g++ -w -c main.cpp -o main.o
dumb.o: dumb.cpp
	g++ -w -c dumb.cpp -o dumb.o
generate.o: generate.cpp
	g++ -w -c generate.cpp -o generate.o

main: main.o
	g++ main.o -o main.out
dumb: dumb.o
	g++ dumb.o -o dumb.out    
generate: generate.o
	g++ generate.o -o generate.out" > Stress

    make -s -f Stress
    if [[ "$?" == "2" ]]
    then
        echo "compilation failed"
        exit 2
    fi

    function runRegular {
        it=1

        while (true)
        do
            ./generate.out > input.txt
            ./main.out < input.txt > output.txt
            ./dumb.out < input.txt > ans.txt
            if (diff output.txt ans.txt)
            then
                ((it=it+1))
                echo -en "\riteration $it"
            else
                echo "error found after $it iterations. check out input.txt, output.txt and ans.txt"
                break
            fi
        done
    }

    export -f runRegular

    echo "starting ..."
    timeout --foreground "$t" bash -c runRegular

    if [ "$?" == "124" ]
    then
        echo "error not found"
    fi

    rm generate.out main.out dumb.out
fi
