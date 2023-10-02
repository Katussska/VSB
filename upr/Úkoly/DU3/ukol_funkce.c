#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

// ANSI escape sequences reference:
// - https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html#cursor-navigation
// - https://tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html

// Height of the drawing canvas
int canvas_height = 40;

//---Cursor management---

// Hide the blinking terminal cursor.
void hide_cursor();

// Show the terminal cursor.
void show_cursor();

//---Color management---

// Reset the drawing and background color to the default values.
void reset_color();

// Set the background color to red.
void set_red_color();

// Set the background color to green.
void set_green_color();

// Set the background color to blue.
void set_blue_color();

//---Screen management---

// Reset the drawing environment.
// Clears the screen, moves the cursor to the origin in the top-left corner and
// prepares the drawing canvas.
void clear_screen();

//---Cursor movement---

// Move cursor right.
void move_right();

// Move cursor left.
void move_left();

// Move cursor up.
void move_up();

// Move cursor down.
void move_down();

// Move cursor to the specified `line` and `column` position.
void move_to(int line, int column);

//---Drawing---

// Draws a single "pixel" using the currently set background color.
// The cursor position is not changed after drawing!
// You need to move the cursor manually before drawing the next pixel,
// otherwise you will just overwrite the previous pixel.
void draw_pixel();

// Clears the drawing session, resets colors and cursor.
// Call this before the end of the program, otherwise your terminal will get messed up.
void end_drawing();

// Pause the program for a while, so that you can see what has been drawn so far.
// If you repeatedly call animate() after drawing something, you can crate interactive animations.
// You can also combine this with clear_screen() to draw something new on every "animation frame".
void animate();

// moje funkce
void cara(int n);
void prerusovana_cara(int n);
void schody(int n);
void posun_doprava(int n);
void posun_nahoru(int n);
void posun_dolu(int n);
void posun_doleva(int n);
void diagonala(int n);
void domecek(int a);
void vesnice(int n);

void hide_cursor()
{
    printf("\x1b[?25l");
}
void show_cursor()
{
    printf("\x1b[?25h");
}

void reset_color()
{
    printf("\x1b[0m");
}
void set_red_color()
{
    printf("\x1b[41;1m");
}
void set_green_color()
{
    printf("\x1b[42;1m");
}
void set_blue_color()
{
    printf("\x1b[44;1m");
}
void clear_screen()
{
    reset_color();
    hide_cursor();

    // Clear screen
    printf("\x1b[2J");
    // Move cursor to (0, 0)
    printf("\x1b[0;0F");
    // Create canvas
    for (int i = 0; i < canvas_height; i++)
    {
        printf("\n");
    }
    for (int i = 0; i < canvas_height; i++)
    {
        printf("\x1b[1A");
    }
}

void move_right()
{
    printf("\x1b[1C");
}
void move_left()
{
    printf("\x1b[1D");
}
void move_up()
{
    printf("\x1b[1A");
}
void move_down()
{
    printf("\x1b[1B");
}
void move_to(int line, int column)
{
    printf("\x1b[%d;%dH", line, column);
}

void draw_pixel()
{
    printf(" ");
    move_left();
}
void end_drawing()
{
    reset_color();
    printf("\x1b[0;0H");
    for (int i = 0; i < canvas_height; i++)
    {
        move_down();
    }
    printf("\n");
    show_cursor();
}
void animate()
{
    fflush(stdout);
    // Sleep for 500ms
    usleep(1000 * 500);
}

void cara(int n)
{
    for (int i = 0; i < n; i++)
    {
        draw_pixel();
        printf(" ");
    }
}
void prerusovana_cara(int n)
{
    for (int i = 0; i < n; i++)
    {
        draw_pixel();
        printf(" ");
        move_right();
    }
}
void schody(int n)
{
    for (int i = 0; i < n; i++)
    {
        draw_pixel();
        draw_pixel();
        move_right();
        move_down();
    }
}

void posun_doprava(int n)
{
    for (int i = 0; i < n; i++)
    {
        move_right();
    }
}
void posun_nahoru(int n)
{
    for (int i = 0; i < n; i++)
    {
        move_up();
    }
}
void posun_dolu(int n)
{
    for (int i = 0; i < n; i++)
    {
        move_down();
    }
}
void posun_doleva(int n)
{
    for (int i = 0; i < n; i++)
    {
        move_left();
    }
}

void diagonala(int n)
{
    posun_doprava(n);
    for (int i = 0; i < n; i++)
    {
        draw_pixel();
        draw_pixel();
        move_left();
        move_down();
    }
}
void domecek(int n)
{
    set_red_color();
    diagonala(n);
    posun_doprava(n + 1);
    posun_nahoru(n);
    schody(n);
    posun_doleva(n + n);
    set_green_color();
    for (int i = 0; i < n; i++)
    {
        cara(n + n);
        move_down();
        posun_doleva(n + n);
    }
}
void vesnice(int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        int r = rand() % (10 + 1 - 3) + 5;
        domecek(r);
        posun_doprava(r + r);
        posun_nahoru(r + r);
        animate();
    }
}
void ctverecek()
{
    draw_pixel();
    move_right();
    draw_pixel();
    move_right();
}
void animace()
{
    set_red_color();
    posun_doprava(2);
    ctverecek();
    animate();
    move_down();
    ctverecek();
    animate();
    move_up();
    ctverecek();
    animate();
    move_down();
    ctverecek();
    animate();
    move_down();
    posun_doleva(2);
    ctverecek(); // je mi jasné, že je to pěkně hnusné, ale bohužel mě tlačil čas, a proto jsem neměla
    animate();   // dostatek času vymyslet pro to cykly, které by tuto funkci zjednodušili
    move_down(); // doufám, že se vám teda aspoň výsledek líbil
    posun_doleva(4);
    ctverecek();
    animate();
    move_down();
    posun_doleva(4);
    ctverecek();
    animate();
    move_up();
    posun_doleva(4);
    ctverecek();
    animate();
    move_up();
    posun_doleva(4);
    ctverecek();
    animate();
    move_up();
    posun_doleva(2);
    ctverecek();
    animate();
}

int main()
{
    // Keep this line here
    clear_screen();

    animace();
    // Keep this line here
    end_drawing();

    return 0;
}