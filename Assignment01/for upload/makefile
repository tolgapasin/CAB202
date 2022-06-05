OBJ=main.o vacuum.o hud.o trash.o collided.o helpers.o timer.o battery.o

# Fix the directories to match your file organisation.
CC_FLAGS=-std=gnu99 -I../../ZDK -Wall -Werror -g
LD_FLAGS=-L../../ZDK -lzdk -lncurses -lm

assignment01: $(OBJ)
	gcc $(OBJ) $(LD_FLAGS) -o $@

%.o : %.c
	gcc -c $< $(CC_FLAGS)
