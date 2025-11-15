#include "liberty.h"
#include <stdlib.h>
#include <stdio.h>


GoGame * readBoard(const char * filename){
    //fill this function to read from the given file and create a GoGame structure
    //both the GoGame struct and it's internal array should be created on the heap
    if (filename == NULL){
        return NULL;
    }
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL){
        return NULL;
    }

    int n;
    if (fscanf(fptr, "%d", & n) != 1){
        fclose(fptr);
        return NULL;
    }

    int space = fgetc(fptr);  //eats the newline between size and matrix
    (void) space;

    GoGame *game = malloc(sizeof(*game));
    if (game == NULL) {
        fclose(fptr);
        return NULL;
    }
    game->size = n;
  
    game->board = malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++){
        int count = 0;
        game->board[i] = malloc((n) * sizeof(char));
        while (count < n){
            int ch = fgetc(fptr);
            if (ch == '\n' || ch == '\r' || ch == ' ' || ch == '\t') {    // skip line breaks
                continue;
            }

            game->board[i][count] = (char) ch;
            count++;
        }
    }
 
    //printf("Board size: %d\n", game->size);
    //printf("Board contents:\n");
    //for (int i = 0; i < game->size; i++) {
    //    for (int j = 0; j < game->size; j++) {
    //        printf("%c", game->board[i][j]);
    //    }
    //    printf("\n");
    //}
    fclose(fptr);
    return game;
}


int getLiberty(GoGame * game, int x, int y){
    //printf("getLiberty called with x=%d y=%d\n", x, y);  // DEBUG
    //Fill in this function to take in a GoGame and find the liberty of the piece at intersection (x,y)
    //Assume (x,y) is always a valid intersection with a piece 

    int liberty = 0;
    int n = game->size;


    char *visited = calloc(n * n, sizeof(char));
    char *counted = calloc(n * n, sizeof(char));

    static int in_progress = 0;             // are we inside recursion?

    // top-level call: clear visited
    if (in_progress == 0) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                visited[i][j] = 0;
                visitedEmpty[i][j] = 0;
            }
        }
    }

    // already explored this stone
    if (visited[x][y]) {
        return 0;
    }
    visited[x][y] = 1;
    in_progress++;

    char color = game->board[x][y];

    // up
    if (x - 1 >= 0) {
        if (game->board[x - 1][y] == '*') {
            if (!visitedEmpty[x - 1][y]) {
                liberty += 1;
                visitedEmpty[x - 1][y] = 1;
            }
        } else if (game->board[x - 1][y] == color) {
            liberty += getLiberty(game, x - 1, y);       // NOTE: x-1, y
        }
    }

    // down
    if (x + 1 < n) {
        if (game->board[x + 1][y] == '*') {
            if (!visitedEmpty[x + 1][y]) {
                liberty += 1;
                visitedEmpty[x + 1][y] = 1;
            }
        } else if (game->board[x + 1][y] == color) {
            liberty += getLiberty(game, x + 1, y);       // NOTE: x+1, y
        }
    }

    // left
    if (y - 1 >= 0) {
        if (game->board[x][y - 1] == '*') {
            if (!visitedEmpty[x][y - 1]) {
                liberty += 1;
                visitedEmpty[x][y - 1] = 1;
            }
        } else if (game->board[x][y - 1] == color) {
            liberty += getLiberty(game, x, y - 1);       // NOTE: x, y-1
        }
    }

    // right
    if (y + 1 < n) {
        if (game->board[x][y + 1] == '*') {
            if (!visitedEmpty[x][y + 1]) {
                liberty += 1;
                visitedEmpty[x][y + 1] = 1;
            }
        } else if (game->board[x][y + 1] == color) {
            liberty += getLiberty(game, x, y + 1);       // NOTE: x, y+1
        }
    }

    in_progress--;
    return liberty;
}

void freeBoard(GoGame * game){
    //Fill this function to free your GoGame structure from the heap
    
    for (int i=0; i < game->size; i++){
        free(game->board[i]);
    }
    free(game->board);
    free(game);
}