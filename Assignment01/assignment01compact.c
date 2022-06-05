#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

// Insert other functions here, or include header files
bool game_over = false;
int delay = 10;
double start_time;

#define VACUUM_DIMENSION 9
#define VACUUM_SPEED 0.2

double vx, vy, vdx, vdy, vacuum_dir;

#define DOCK_DIMENSION 9


char * vacuum =
"  @@@@@  "
" @-----@ "
"@-------@"
"@-------@"
"@-------@"
"@-------@"
"@-------@"
" @-----@ "
"  @@@@@  "
;

char * dock =
"#########"
"#########"
"#########"
"#########"
"#########"
"#########"
"#########"
"#########"
"#########"
;

void draw_pixels ( 
    int left, 
    int top, 
    int width, 
    int height, 
    char bitmap[], 
    bool space_is_transparent
) {

    for ( int j = 0; j < height; j++ ) {
        for ( int i = 0; i < width; i++ ) {
            if ( bitmap[i+j * width] != ' ') {
                draw_char(left+i, top+j, bitmap[i+j*width]);
            } else if ( !space_is_transparent ) {
                draw_char( left+i, top+j, ' ');
            }
        }
    }
}

void draw_vacuum() {
    int screen_w, screen_h;
    get_screen_size(&screen_w, &screen_h);
    //UPDATE PARAMETERS OF NEXT FUNCTION!!!
    draw_pixels(vx, vy, VACUUM_DIMENSION, VACUUM_DIMENSION, vacuum, true);
}

void draw_status_bar() {
    int screen_w, screen_h;
    get_screen_size(&screen_w, &screen_h);
    const int chTop = '-';
    const int chSides = '|';
    const int intersect = '+';

  
    double get_time = get_current_time();

    draw_line(0, 2, screen_w - 1, 2, chTop);
    
    draw_line(0, 4, screen_w - 1, 4, chTop);
    
    draw_line(screen_w/3, 0, screen_w/3, 4, chSides);

    draw_line(screen_w/1.5, 0, screen_w/1.5, 4, chSides);

    draw_char(0, 2, intersect);
    draw_char(0, 4, intersect);

    draw_char(screen_w/3, 0, intersect);
    draw_char(screen_w/1.5, 0, intersect);

    draw_char(screen_w/3, 2, intersect);
    draw_char(screen_w/1.5, 2, intersect);

    draw_char(screen_w/3, 4, intersect);
    draw_char(screen_w/1.5, 4, intersect);

    draw_char(screen_w-1, 2, intersect);
    draw_char(screen_w-1, 4, intersect);
    
    // Row 1, Column 1
    draw_string(2, 1, "Student #: n9737197");

    // Row 1, Column 2
    draw_formatted(screen_w/3+2, 1, "Robot Direction: %f", vacuum_dir);

    // Row 1, Column 3
    draw_string(screen_w/1.5+2, 1, "Battery Life: ");

    // Row 2, Column 1
    draw_formatted(2, 3, "Time Elapsed: %f", get_time);

    // Row 2, Column 2
    draw_string(screen_w/3+2, 3, "Load Weight: ");

    // Row 2, Column 3
    draw_string(screen_w/1.5+2, 3, "Rubbish Available: ");
    
}

void draw_border() {
    int screen_w, screen_h;
    get_screen_size(&screen_w, &screen_h);
    const int chTop = '-';
    const int chSides = '|';
    const int intersect = '+';
    //const int intersect = '+';
    //draw_line(x1, y1, x2, y2);

   

    draw_line(0, 0, 0, screen_h - 1, chSides);
    draw_line(0, 0, screen_w - 1, 0, chTop);
    draw_line(0, screen_h - 1, screen_w - 1, screen_h - 1, chTop);
    draw_line(screen_w - 1, 0, screen_w - 1, screen_h - 1, chSides);
    draw_char(0, 0, intersect);
    draw_char(0, screen_h-1, intersect);
    draw_char(screen_w-1, 0, intersect);
    draw_char(screen_w-1, screen_h-1, intersect);
}

void draw_charging_dock() {
    int screen_w, screen_h;
    get_screen_size(&screen_w, &screen_h);
    int dock_x = screen_w/2 - DOCK_DIMENSION /2;
    int dock_y = 5;
    draw_pixels( dock_x, dock_y, DOCK_DIMENSION, DOCK_DIMENSION, dock, false);
    
}

void draw_all() {
    clear_screen();
    draw_border();
    draw_status_bar();
    draw_vacuum();
    draw_charging_dock();
    show_screen();
}

void setup_vacuum() {
    int screen_w, screen_h;
    get_screen_size(&screen_w, &screen_h);

    vx = (screen_w-VACUUM_DIMENSION)/2;
    vy = (screen_h-VACUUM_DIMENSION)/2;
    
    vacuum_dir = rand() * 2 * M_PI / RAND_MAX; //DIRECTION
    const double step = VACUUM_SPEED;

    vdx = step * cos(vacuum_dir);
    vdy = step * sin(vacuum_dir);

}

void update_vacuum_pos() {
    int new_x = round(vx + vdx) - VACUUM_DIMENSION / 2; 
    int new_y = round(vy + vdy) - VACUUM_DIMENSION / 2;

    bool bounced = false;

    if(new_x +3 == 0 || new_x + VACUUM_DIMENSION +3 == screen_width()) {
        //horizontal bounce
        vdx = -vdx;
        bounced = true;
    }

    if (new_y -1 == 0 || new_y + VACUUM_DIMENSION +4 == screen_height()) {
        // vertical bounce
        vdy = -vdy;
        bounced = true;
    }

    if (!bounced) {
        vx += vdx;
        vy += vdy;
    }
   
}

void setup () {
    // Insert setup logic here
    //override_screen_size(50, 150);
    start_time = get_current_time();
    setup_vacuum();
    draw_all();
    
}

void loop() {
    // Insert loop logic here.
    update_vacuum_pos();
    draw_all();
}

int main() {
    setup_screen();
    setup();

    while ( !game_over ) {
        loop();
        timer_pause( delay );
    }

    return 0;
}

