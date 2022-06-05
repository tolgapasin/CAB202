#!/bin/bash

test_num=0
REPORT_FILE=assignment01_report.txt

echo "Remember to do these two commands before running this script:
export COLUMNS
export LINES:
Suggested (150, 50).
"
echo "Test run starting at $(date)" >>${REPORT_FILE}

#==============================================================================
#	Available operations for vacuum simulation.
#==============================================================================

function move_vacuum () {
	printf "v${1},${2},${3} " 
}

function set_battery () {
	printf "y${1} "
}

function return_to_base () {
	printf "b "
}

function set_timeout () {
	printf "o${1} "
}

function set_weight () {
	printf "w${1} "
}

function set_delay () {
	printf "m${1} "
}

function pause_resume () {
	printf "p "
}

function reset () {
	printf "r${1} "
}

function left () {
	printf "j "
}

function right () {
	printf "l "
}

function up () {
	printf "i "
}

function down () {
	printf "k "
}

function quit () {
	printf "q "
}

function help_screen () {
	printf "? "
}

function drop_dust () {
	printf "d${1},${2} "
}

function drop_slime () {
	printf "s${1},${2} "
}

function drop_trash () {
	printf "t${1},${2} "
}

function loop () {
	if (( $# >= 1 )) && (( $1 > 0 )) 
	then
		for (( i = 0; i < $1; i++ ))
		do
			printf "!"
		done
	else
		printf "!"
	fi
}

function enter () {
	printf "${1} "
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
		echo ${cmd} | ./assignment01
		read -p "Did the test pass or fail (p/f)? " result
		echo "Test ${test_num}: ${result}" >>${REPORT_FILE}
	fi
}

#==============================================================================
category="Test Item 1, 2, 3 and 4: Robotic Vacuum Setup"
details="Vacuum and status bar are displayed."
expect="Vacuum appears in middle of screen. Status bar is set to default values."

cmd=$(
	enter 0
    enter 0
    enter 0
	pause_resume
	set_timeout 5
	pause_resume
)

run_test 

#==============================================================================
category="Test Item 6, 14 and 7: Robotic Vacuum Default Behaviour"
details="Vacuum is displayed then shows normal movement and the battery is functional."
expect="Vacuum appears in the middle of the screen, moves directly downward by 0.2 screen units per time slice. It then bounces off the wall at an angle between 30 and 60 degrees. The battery will decrement by 1 every second."

cmd=$(
	enter 0
	enter 0
	enter 0
	pause_resume
	set_timeout 5
	
)

run_test 


#==============================================================================
category="Test Item 15: Move Vacuum with Input"
details="With user input, the vacuum is moved to the right, left, up and down."
expect="The vacuum is paused, the 'l', 'j', 'i' and 'k' keys are inputted, moving the vacuum to the right, left, up and down 10 places each."


cmd=$(
	enter 0
	enter 0
	enter 0
	pause_resume
	set_timeout 3
	pause_resume
	for (( i = 0; i < 10; i++ ))
		do
			right
		done

	for (( i = 0; i < 10; i++ ))
		do
			left
		done

	for (( i = 0; i < 10; i++ ))
		do
			up
		done

	for (( i = 0; i < 10; i++ ))
		do
			down
		done
	
)

run_test 

#==============================================================================
category="Test Item 15: Quit Simulation"
details="With user input, the simulation is exited."
expect="The character 'q' is inputted, bringing up a goodbye screen. After that another random character is inputted to exit the simulation."

cmd=$(
	enter 0
	enter 0
	enter 0
	pause_resume
	set_timeout 5
	set_delay 1000
	quit
	loop 500
	enter a

)

run_test 

#==============================================================================
category="Test Item 15: Increase Delay"
details="With user input, the delay time is increased"
expect="The character 'm' is inputted and the delay is specified to 30 this will slow down the simulations movement."

cmd=$(
	enter 0
	enter 0
	enter 0
	pause_resume
	set_delay 50
	set_timeout 3
	
)

run_test 

#==============================================================================
category="Test Item 15: Move Vacuum Cheat"
details="With user input, the vacuum jumps to a new location."
expect="The character 'v' is inputted and the vacuum jumps to a the specified location 10, 10 with a heading of 0."

cmd=$(
	enter 0
	enter 0
	enter 0
	pause_resume
	move_vacuum 10 10 0
	set_timeout 3
	
)

run_test

### Test will not time out. Therefore it is commented out.
#==============================================================================
# category="Test Item 15: Help Screen"
# details="With user input, the the help screen is brought up."
# expect="The character '?' is inputted and a help screen is brought up to inform the user of all the available command inputs. It is then exited when any key is entered."

# cmd=$(
# 	enter 0
# 	enter 0
# 	enter 0
# 	pause_resume
# 	set_timeout 3
# 	set_delay 1000
# 	help_screen 
# 	enter a
	
# )

# run_test

#==============================================================================
category="Test Item 14: Collision with Dock"
details="The vacuum will collid with the dock and respond appropriately."
expect="The delay is set to 1 to speed up the vacuum. The robot will eventually collide with the dock a few times. When this happens it will bounce off of it at an angle between 30 and 60 degrees."

cmd=$(
	enter 0
	enter 0
	enter 0
	pause_resume
	set_delay 1
	set_timeout 5
	
)

run_test 

#==============================================================================
category="Test Item 7: Battery at 25%"
details="The vacuum returns to base when battery is at 25%."
expect="The battery is set to 25%. As a result the vacuum returns to the charging dock to charge. While returning, it should not pick up any rubbish. It then charges to 100% and continues normal functionality."

cmd=$(
	enter 0
	enter 0
	enter 0
	pause_resume
	set_battery 25
	set_timeout 5
	
)

run_test 

#==============================================================================
category="Test Item 10: Battery at 0%"
details="The vacuum reacts appropriately when the battery is at 0%."
expect="The battery is set to 0% manually. The vacuum is then immobilised as a result and a screen will appear asking the user to enter 'q' to quit or 'r' to reset."

cmd=$(
	enter 0
	enter 0
	enter 0
	pause_resume
	set_battery 0
	set_timeout 5
)

run_test 

#==============================================================================
category="Test Item 12 and 13: Rubbish Collection"
details="The vacuum correctly collects the rubbish of each type."
expect="Many pieces of rubbish are spread out over the room. When the vacuum passes over them, they dissapear and the weight in the status bar increases by 1g for dust, 5g for slime and 20g for trash each time."

cmd=$(
	enter 30
	enter 10
	enter 5
	pause_resume
	set_timeout 5
)


run_test

#==============================================================================
category="Test Item 11: Load Carrying Capacity"
details="The device operates normally up until max load weight occurs."
expect="The character 'w' will be inputted to set the devices weight will to 45g. It will then return to base and drop off its load."

cmd=$(
	enter 50
	enter 10
	enter 5
	pause_resume
	set_weight 45
	set_timeout 5
)

run_test

#==============================================================================
category="Test Item 15: Drop Rubbish Cheats"
details="With user input, a piece of dust, slime and trash is dropped on the screen."
expect="The characters 'd', 's' and 't' are inputted and a piece of dust, slime and trash is dropped at the specified locations (10, 10), (20, 20) and (30, 10)."

cmd=$(
	enter 0
	enter 0
	enter 0
	pause_resume
	drop_dust 10 10
	drop_slime 20 20
	drop_trash 30 10
	set_timeout 3
	
)

run_test


#==============================================================================
category="Test Item 9 and 15: Return to Base"
details="The vacuum returns to base."
expect="When the command 'b' is inputted, the vacuum sets its heading towards the charging dock and moves towards there. While returning, it should not pick up any rubbish. It then charges to 100% and continues normal functionality."

cmd=$(
	enter 0
	enter 0
	enter 0
	pause_resume
	return_to_base
	set_timeout 5
)

run_test 


#==============================================================================
category="Test Item 15: Reset Simulation"
details="With user input, the simulation is reset."
expect="The character 'r' is inputted this will reset the simulation to the beggining."

cmd=$(
	enter 0
	enter 0
	enter 0
	pause_resume
	set_timeout 3
	enter r
	loop 500
	pause_resume
	
)

run_test 

