/**
 * fifteen.c
 *
 * Computer Science 50
 * Problcd\em Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *./fifteen
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true){
        
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        printf("\n");
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
   // printf("\033[2J");
   // printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    
    int make = d*d;
    
    for(int n=0;n<9;n++){
        for(int m=0;m<9;m++){
            board[n][m] = 99;
        }
    }
    
    for(int n=0;n<d;n++){
        for(int m=0;m<d;m++){
            make--;
            board[n][m] = make;
        }
    }
    
    
    if(d==4){
        board[3][1] = 1;
        board[3][2] = 2;
    }
    
    if(d==6){
        board[5][3] = 1;
        board[5][4] = 2;
    }
    
    if(d==8){
        board[7][5] = 1;
        board[7][6] = 2;
    }
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    for(int n=0;n<d;n++){
        for(int m=0;m<d;m++){
            if(board[n][m] < 10){
                printf(" ");
            }
            
            if(board[n][m] == 0){
                printf("_  ");
            }else
                printf("%i  ", board[n][m]);
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{

    //input validation
    if((tile > (d*d)) || (tile < 1)){
        return false;
    }
    
    int xSpace = 0;
    int ySpace = 0;
    
    int xTile = 0;
    int yTile = 0;
    
    //find space co-ordinates
    for(int y=0;y<d;y++){
        for(int z=0;z<d;z++){
            if(board[y][z] == 0){
                xSpace = y;
                ySpace = z;
            }
        }
    }
    //printf("Space position is board[%i][%i] \n", xSpace, ySpace);
    
    //find tile co-ordinates
    for(int s =0;s<d;s++){
        for(int t=0;t<d;t++){
            if(board[s][t] == tile){
                xTile = s;
                yTile = t;
            }

        }
    }
    //printf("Tile position %i %i \n", xTile, yTile);
    
   //printf("if %i \n", board[xTile+1][yTile]);
   
   
    //move selected tile down, if allowed, to swap with 0 tile
    if(board[xTile+1][yTile] == 0){ 
        board[xSpace][ySpace] = board[xTile][yTile];
        board[xTile][yTile] = 0;
        return true;
    }
    
    //move selected tile up, if allowed, to swap with 0 tile
    if(board[xTile-1][yTile] == 0){ 
        board[xSpace][ySpace] = board[xTile][yTile];
        board[xTile][yTile] = 0;
        return true;
    }
    
      //move selected tile right, if allowed, to swap with 0 tile
    if(board[xTile][yTile+1] == 0){ 
        board[xSpace][ySpace] = board[xTile][yTile];
        board[xTile][yTile] = 0;
        return true;
    }
    
      //move selected tile left, if allowed, to swap with 0 tile
    if(board[xTile][yTile-1] == 0){ 
        board[xSpace][ySpace] = board[xTile][yTile];
        board[xTile][yTile] = 0;
        return true;
    }
   
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int cd = 0;
    
    if(board[d-1][d-1] != 0){
        
        return false;
    }
        
    board[d-1][d-1] = (d*d);
    
    for(int w=0;w<d;w++){
       for(int x=0;x<d;x++){
           cd++;
           if(board[w][x] != cd){
                board[d-1][d-1] = 0;
               return false;
           }
       }
   }
    
    return true;
}