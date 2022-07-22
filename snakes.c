#include <dani1.h>
#include <dani1/danivga.h>
#include <dani1/dcursor.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "snakegfx.h"

#define BOARD_HEIGHT (DANI_SCREEN_HEIGHT-1)
#define BOARD_WIDTH  DANI_SCREEN_WIDTH

#define DIR_RIGHT 0
#define DIR_LEFT  1
#define DIR_UP    2
#define DIR_DOWN  3

struct Snake {
    unsigned char x;
    unsigned char y;
    unsigned char direction;
};

unsigned char direction = DIR_RIGHT;
unsigned char input = 0;
unsigned char gameover = 0;
char scoreBuffer[DANI_SCREEN_WIDTH];

struct Snake currentHead;
struct Snake snake[BOARD_WIDTH * BOARD_HEIGHT] = {{2,0,DIR_RIGHT},{1,0,DIR_RIGHT}};
unsigned int snakelen = 2;

void updateScore() {
    sprintf(scoreBuffer,"SCORE: %u",snakelen-2);
    dcurxy(textCenter(scoreBuffer),DANI_SCREEN_HEIGHT-1);
    printf(scoreBuffer);
}

void placeFood() {
    unsigned char apple_x, apple_y;
    do {
        apple_x = rand() % BOARD_WIDTH;
        apple_y = rand() % BOARD_HEIGHT;
    } while (getcxy(apple_x, apple_y) != 0);
    dplotcxy(apple_x, apple_y, GFX_FOOD);
}

void processInput() {
    input = agetch();

    switch (input) {
        case 0x83: /* right */
            if (direction != DIR_LEFT) {
                direction = DIR_RIGHT;
            }      
        break;
        case 0x82: /* left */
            if (direction != DIR_RIGHT) {
                direction = DIR_LEFT;
            }
        break;
        case 0x80: /* up */
            if (direction != DIR_DOWN) {
                direction = DIR_UP;
            }
        break;
        case 0x81: /* down */
            if (direction != DIR_UP) {
                direction = DIR_DOWN;
            }
        break;
    }
}

void moveSnake() {
    unsigned int i = 0;
    currentHead.x = snake[0].x;
    currentHead.y = snake[0].y;
    currentHead.direction = direction;
    switch (direction) {
        case DIR_RIGHT:
            if (++currentHead.x == BOARD_WIDTH) {
                currentHead.x = 0;
            }
        break;
        case DIR_LEFT:
            if (--currentHead.x == 255) {
                currentHead.x = BOARD_WIDTH-1;
            }
        break;
        case DIR_UP:
            if (--currentHead.y == 255) {
                currentHead.y = BOARD_HEIGHT-1;
            }
        break;
        case DIR_DOWN:
            if (++currentHead.y == BOARD_HEIGHT) {
                currentHead.y = 0;
            }
        break;
    }
    for (i = snakelen; i > 0; i--){
        snake[i].x = snake[i-1].x;
        snake[i].y = snake[i-1].y;
        snake[i].direction = snake[i-1].direction;
    }
    snake[0].x = currentHead.x;
    snake[0].y = currentHead.y;
    snake[0].direction = currentHead.direction;
}

void draw() {
    unsigned char headpiece;
    unsigned char tailpiece;
    switch (snake[0].direction) {
        case DIR_UP:
        headpiece = GFX_SNAKEHEAD_UP;
        break;
        case DIR_DOWN:
        headpiece = GFX_SNAKEHEAD_DOWN;
        break;
        case DIR_LEFT:
        headpiece = GFX_SNAKEHEAD_LEFT;
        break;
        case DIR_RIGHT:
        headpiece = GFX_SNAKEHEAD_RIGHT;
        break;
    }
    switch (snake[snakelen-2].direction) {
        case DIR_UP:
        tailpiece = GFX_SNAKETAIL_UP;
        break;
        case DIR_DOWN:
        tailpiece = GFX_SNAKETAIL_DOWN;
        break;
        case DIR_LEFT:
        tailpiece = GFX_SNAKETAIL_LEFT;
        break;
        case DIR_RIGHT:
        tailpiece = GFX_SNAKETAIL_RIGHT;
        break;
    }
    dplotcxy(snake[snakelen].x,snake[snakelen].y,0);
    dplotcxy(snake[0].x,snake[0].y,headpiece);
    dplotcxy(snake[1].x,snake[1].y,GFX_SNAKEBODY);
    dplotcxy(snake[snakelen-1].x, snake[snakelen-1].y, tailpiece);
    sleep(5);
}

void loadGfx() {
    unsigned char x;
    for (x = 0; x < GFX_TILECOUNT; ++x) {
        dstorechar(&gfx_tiles[x], GFX_START+x);
    }
}

void checkCollision() {
    unsigned char cell = getcxy(snake[0].x,snake[0].y); // Check cell to see if there is anything there before draw
    if (cell == GFX_FOOD) {
        snakelen++;
        placeFood();
        updateScore();
    } else if(cell >= GFX_START && cell <= (GFX_START+GFX_TILECOUNT-2) ) {
        // These are all body pieces
        gameover = 1;
    }
}

void intro() {
    char title[] = "DANI-I Snakes!";
    char directions[] = "Arrows = Directions, Esc to Quit";
    blankscreen();
    dcurxy(textCenter(title),14);
    fputs(title, stdout);
    dcurxy(textCenter(directions),29);
    fputs(directions, stdout);
    while (!agetch()); // Wait for a key to be pressed
}

void main(void)
{   
    time_t t;
    
    gameover = 0;
    snakelen = 2;
    input = 0;

    srand(time(&t));
    loadGfx();
    intro();
    blankscreen();
    draw();
    placeFood();
    updateScore();

    while (input != 0x1B && !gameover) {
        processInput();
        moveSnake();
        checkCollision();
        draw();
    }

    blankscreen();
    printf("Final Score of %u\n\n", snakelen-2);
}