/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
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
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
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
        int tile = get_int();
        
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
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
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
    int random=0;
    int Limit;
    bool sovpadeniy;
    Limit=d*d-1;

    srand(time(NULL));
    
    for (int i=1; i<=d;i++)
    {
         for (int j=1; j<=d;j++)
            {
                if ((i!=d)||(j!=d))
                {
                      do
                       {    sovpadeniy=false;
                            random =1+rand() %Limit;
                            
                            for (int i1=1; i1<=d;i1++)
                            { 
                                 for (int j1=1; j1<=d;j1++)
                                 {
                                   if(board[i1][j1]==random)  
                                    //   printf("%d = %d \n",board[i1][j1],random);
                                     sovpadeniy=true;  
                                 }
                            }
                        }while(sovpadeniy);
                        
                 board[i][j]=random;
                }
            }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
     for (int i=1; i<=d;i++)
    {
         for (int j=1; j<=d;j++)
            {   
                if (board[i][j]!=0)
                {
                    if(board[i][j]<10)
                    printf(" %d ",board[i][j]);
                    else printf("%d ",board[i][j]);
                }
                else printf(" _ ");
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
    // TODO
    // 1 2 3
    // 4 5 6
    // 7 8 _
      for (int i=1; i<=d;i++)
    {
         for (int j=1; j<=d;j++)
            {   
                if (board[i][j]==tile)
                {
                   
                    if (((i+1)<=d)&&((j+1)<=d)&&((j-1)>=1)&&((i-1)>=1)) //element ne kasaetsya "stenok" matrici
                    {
                        if(board[i-1][j]==0)
                        {
                            board[i-1][j]=tile;
                            board[i][j]=0;
                            return true;
                        }
                        
                        if(board[i+1][j]==0)
                        {
                            board[i+1][j]=tile;
                            board[i][j]=0;
                             return true;
                        }
                        
                        if(board[i][j+1]==0)
                        {
                            board[i][j+1]=tile;
                            board[i][j]=0;
                             return true;
                        }
                            
                        if(board[i][j-1]==0)
                        {
                            board[i][j-1]=tile;
                            board[i][j]=0;
                             return true;
                        }
                    }
                    
                     if ((i==1)&&(j==1)) //pervuy element mesiva
                    {
                        if(board[i+1][j]==0)
                        {
                            board[i+1][j]=tile;
                            board[i][j]=0;
                             return true;
                        }
                        
                        if(board[i][j+1]==0)
                        {
                            board[i][j+1]=tile;
                            board[i][j]=0;
                             return true;
                        }
                    }
                       
                        if ((i==d)&&(j==d)) //posledniy element mesiva
                    {
                        if(board[i-1][j]==0)
                        {
                            board[i-1][j]=tile;
                            board[i][j]=0;
                            return true;
                        }
                        
                        if(board[i][j-1]==0)
                        {
                            board[i][j-1]=tile;
                            board[i][j]=0;
                             return true;
                        }
                    }
                    
                   if ((i==1)&&(j==d)) //pravuy verhniy ygol
                    {
                        if(board[i+1][j]==0)
                        {
                            board[i+1][j]=tile;
                            board[i][j]=0;
                             return true;
                        }
                        
                        if(board[i][j-1]==0)
                        {
                            board[i][j-1]=tile;
                            board[i][j]=0;
                             return true;
                        }
                    }
                    
                     if ((i==d)&&(j==1))//nigniy levuy ygol
                    {
                        if(board[i-1][j]==0)
                        {
                            board[i-1][j]=tile;
                            board[i][j]=0;
                            return true;
                        }
                        
                        if(board[i][j+1]==0)
                        {
                            board[i][j+1]=tile;
                            board[i][j]=0;
                             return true;
                        }
                    }
                    
                 if ((i==1)&&(j>1)&&(j<d)) //pervoya stroka, ne vozle kraya
                    {
                        if(board[i+1][j]==0)
                        {
                            board[i+1][j]=tile;
                            board[i][j]=0;
                             return true;
                        }
                        
                        if(board[i][j+1]==0)
                        {
                            board[i][j+1]=tile;
                            board[i][j]=0;
                             return true;
                        }
                            
                        if(board[i][j-1]==0)
                        {
                            board[i][j-1]=tile;
                            board[i][j]=0;
                             return true;
                        }
                    }
                    
                   if ((i==d)&&(j>1)&&(j<d))//poslednya stroka, ne vozle kraya
                    {
                        if(board[i-1][j]==0)
                        {
                            board[i-1][j]=tile;
                            board[i][j]=0;
                            return true;
                        }
                        
                        if(board[i][j+1]==0)
                        {
                            board[i][j+1]=tile;
                            board[i][j]=0;
                             return true;
                        }
                            
                        if(board[i][j-1]==0)
                        {
                            board[i][j-1]=tile;
                            board[i][j]=0;
                             return true;
                        }
                    }  
                    
                     if ((j==1)&&(i>1)&&(i<d)) //levuy krayniy element
                    {
                        if(board[i-1][j]==0)
                        {
                            board[i-1][j]=tile;
                            board[i][j]=0;
                            return true;
                        }
                        
                        if(board[i+1][j]==0)
                        {
                            board[i+1][j]=tile;
                            board[i][j]=0;
                             return true;
                        }
                        
                        if(board[i][j+1]==0)
                        {
                            board[i][j+1]=tile;
                            board[i][j]=0;
                             return true;
                        }
                    }
                   
                    if ((j==d)&&(i>1)&&(i<d)) //element pravuy kray
                    {
                        if(board[i-1][j]==0)
                        {
                            board[i-1][j]=tile;
                            board[i][j]=0;
                            return true;
                        }
                        
                        if(board[i+1][j]==0)
                        {
                            board[i+1][j]=tile;
                            board[i][j]=0;
                             return true;
                        }
                        
                        if(board[i][j-1]==0)
                        {
                            board[i][j-1]=tile;
                            board[i][j]=0;
                             return true;
                        }
                    } 
                   
                }
            }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    int znachenie=d*d-1;

    for (int i=1; i<=d;i++)
    {
         for (int j=1; j<=d;j++)
            {   
                if (board[i][j]!=znachenie)
                    return false;
                
                znachenie--;
            }
    }
    return true;
}
