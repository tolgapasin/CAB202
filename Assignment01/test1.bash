#!/bin/bash

test_num=0
REPORT_FILE=test_report.txt

echo "Test run starting at $(date)" >>${REPORT_FILE}

#==============================================================================
#	Operations available in the ZDJ2 simulation.
#==============================================================================
function move_zombie () {
	printf "z${1},${2},${3},${4} " 
}

function move_hero () {
	printf "h${1},${2} " 
}

function set_timeout () {
	printf "t${1} "
}

function set_delay () {
	printf "m${1}"
}

function pause_resume () {
	printf "p "
}

function reset () {
	printf "r${1} "
}

function left () {
	printf "a "
}

function right () {
	printf "d "
}

function up () {
	printf "w "
}

function down () {
	printf "s "
}

#========================================================================
#	Run a single test.
#========================================================================	

function run_test () {
	(( test_num ++ ))
	echo "Test    : ${test_num}"
	echo "Category: ${category}"
	echo "Details : ${details}"
	echo "Expect  : ${expect}"
	
	read -p "Press r to run the test or s to skip..." run_or_skip
	
	if [ "${run_or_skip}" == "r" ]
	then
		echo ${cmd} | ./assignment
		read -p "Did the test pass or fail (p/f)? " result
		echo "Test ${test_num}: ${result}" >>${REPORT_FILE}
	fi
}

#==============================================================================
category="Setup hero"
details="Hero alone in center of small terminal window."
expect="Hero is displayed in centre; no zombie is visible."

cmd=$(
	echo "1 "
	pause_resume
	move_zombie 0 1000 1000 0
	set_timeout 5
)

run_test 
#==============================================================================
category="Setup zombie"
details="Hero and 1 zombies."
expect="Hero is displayed in centre; 1 zombie is visible; none overlap the hero or the border."

cmd=$(
	echo "1 "
	pause_resume
	set_timeout 5
)

run_test 
#==============================================================================
category="Setup zombie"
details="Hero and 3 zombies."
expect="Hero is displayed in centre; 3 zombies are visible; none overlap the hero or the border."

cmd=$(
	echo "3 "
	pause_resume
	set_timeout 5
)

run_test 
#==============================================================================
category="Setup zombie"
details="Hero and 5 zombies."
expect="Hero is displayed in centre; 5 zombies are visible; none overlap the hero or the border."

cmd=$(
	echo "5 "
	pause_resume
	set_timeout 5
)

run_test 
#==============================================================================
category="Setup zombie"
details="Hero and 10 zombies."
expect="Hero is displayed in centre; 10 zombies are visible; none overlap the hero or the border."

cmd=$(
	echo "10 "
	pause_resume
	set_timeout 5
)

run_test
#==============================================================================
category="Setup Hero"
details="Hero"
expect="Hero is displayed in centre."

cmd=$(
	echo "1 "
	pause_resume
    move_zombie 0 1000 1000 0
	set_timeout 5
)

run_test  
#==============================================================================
category="Update Hero"
details="Hero"
expect="Hero moves up 10 spaces."

cmd=$(
    echo "1 "
    pause_resume
    move_zombie 0 1000 1000 0
    for (( i = 0; i <= 10; i++))
    do
        up
    done
    set_timeout 5
)

run_test
#==============================================================================
category="Do Hero Cheat"
details="Hero"
expect="Hero moves to specified location"

cmd=$(
    echo "1 "
    pause_resume
    hero_cheat 10 10
    set_timeout 5
)

run_test
