#include<bits/stdc++.h>
#include<ctype.h>
using namespace std;
struct Move
{
    int row, col;
};
char player = 'O', opponent = 'X';
char board[5][5];
int turn=0;
void print()
{
                for(int i=1;i<=3;i++)
                {
                    cout<<"\t\t\t\t";

                    for(int j=1;j<=3;j++)
                    {
                        if(j==1)
                            cout<<"| ";
                        cout<<board[i][j]<<" | ";
                    }

                    cout<<"\n\n";
                }
}
int isover(char check)
{
    if(board[1][1]==check&&board[1][2]==check&&board[1][3]==check)
        return 1;
    else if(board[1][1]==check&&board[2][1]==check&&board[3][1]==check)
        return 1;
    else if(board[3][1]==check&&board[3][2]==check&&board[3][3]==check)
        return 1;
    else if(board[1][3]==check&&board[2][3]==check&&board[3][3]==check)
        return 1;
    else if(board[1][2]==check&&board[2][2]==check&&board[3][2]==check)
        return 1;
    else if(board[2][1]==check&&board[2][2]==check&&board[2][3]==check)
        return 1;
    else if(board[1][1]==check&&board[2][2]==check&&board[3][3]==check)
        return 1;
    else if(board[1][3]==check&&board[2][2]==check&&board[3][1]==check)
        return 1;
    return 0;
}
int isgameover()
{
    char check;
    if(turn==0)
        check='X';
    else
        check='O';
    if(isover(check))
        return 1;
    int c=0;
    for(int i=1;i<=3;i++)
    {
        for(int j=1;j<=3;j++)
        {
            if(board[i][j]=='-')
                c++;
        }
    }
    if(c==0)
        return -1;
    else
        return 0;
}
bool isMovesLeft(char board[5][5])
{
    for (int i = 1; i<=3; i++)
        for (int j = 1; j<=3; j++)
            if (board[i][j]=='-')
                return true;
    return false;
}

int evaluate(char b[5][5])
{
    for (int row = 1; row<=3; row++)
    {
        if (b[row][1]==b[row][2] &&
            b[row][2]==b[row][3])
        {
            if (b[row][1]==player)
                return +10;
            else if (b[row][1]==opponent)
                return -10;
        }
    }
    for (int col = 1; col<=3; col++)
    {
        if (b[1][col]==b[2][col] &&
            b[2][col]==b[3][col])
        {
            if (b[1][col]==player)
                return +10;

            else if (b[1][col]==opponent)
                return -10;
        }
    }
    if (b[1][1]==b[2][2] && b[3][3]==b[2][2])
    {
        if (b[1][1]==player)
            return +10;
        else if (b[1][1]==opponent)
            return -10;
    }
    if (b[1][3]==b[2][2] && b[2][2]==b[3][1])
    {
        if (b[1][3]==player)
            return +10;
        else if (b[1][3]==opponent)
            return -10;
    }
    return 0;
}
int minimax(char board[5][5], int depth, bool isMax)
{
    int score = evaluate(board);
    if (score == 10)
        return score;
    if (score == -10)
        return score;
    if (isMovesLeft(board)==false)
        return 0;
    if (isMax)
    {
        int best = -1000;
        for (int i = 1; i<=3; i++)
        {
            for (int j = 1; j<=3; j++)
            {
                if (board[i][j]=='-')
                {
                    board[i][j] = player;
                    best = max( best,
                        minimax(board, depth+1, !isMax) );
                    board[i][j] = '-';
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;
        for (int i = 1; i<=3; i++)
        {
            for (int j = 1; j<=3; j++)
            {
                if (board[i][j]=='-')
                {
                    board[i][j] = opponent;
                    best = min(best,
                           minimax(board, depth+1, !isMax));
                    board[i][j] = '-';
                }
            }
        }
        return best;
    }
}
Move findBestMove(char board[5][5])
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;
    for (int i = 1; i<=3; i++)
    {
        for (int j = 1; j<=3; j++)
        {
            if (board[i][j]=='-')
            {
                board[i][j] = player;
                int moveVal = minimax(board, 0, false);
                board[i][j] = '-';
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}
int main()
{
    cout<<"1:play game 2:instructions 3:exit"<<endl;
    int ch;
    while(cin>>ch)
    {
        system("cls");
        if(ch==3)
            break;
        else if(ch==2)
        {
            cout<<"The object of Tic Tac Toe is to get three in a row. You play on a three by three game board."<<
                  "The first player is known as X and the second is O. Players alternate placing Xs and Os on the game board"<<
                    "until either oppent has three in a row or all nine squares are filled. X always goes first,"<<
                    "and in the event that no one has three in a row, the stalemate is called a cat game.\n\n\n";
        }
        else
        {
            cout<<"1: one player 2: two player"<<endl;
            int ch2;
            cin>>ch2;
            system("cls");
            if(ch2==1)
            {
                cout<<"\t\t\t TIC TAC TOE by Bhaskar Nihaal\n\n\n";
                for(int i=1;i<=3;i++)
                    for(int j=1;j<=3;j++)
                        board[i][j]='-';
                print();
                cout<<"\n\n Enter the location in the form of x and y (ex: 1,1)\n";
                int x,y;
                while(1)
                {
                    if(turn==0)
                    {
                        cin>>x>>y;
                        if(board[x][y]!='-'||x<1||x>3||y<1||y>3)
                        {
                            cout<<"Enter valid move"<<endl;continue;
                        }
                        board[x][y]='X';
                    }
                    else
                    {
                        Move bestMove = findBestMove(board);
                        board[bestMove.row][bestMove.col]='O';
                    }
                    system("cls");
                    cout<<"\t\t\t TIC TAC TOE by Bhaskar Nihaal\n\n\n";
                    print();
                    int result=isgameover();
                    turn=1-turn;
                    if(result==1)
                    {
                        if(turn==1)
                            cout<<"Congratulations You Won"<<endl;
                        else
                            cout<<"You Lose Better Luck Next Time"<<endl;
                        break;
                    }
                    else if(result==-1)
                    {
                        cout<<"Draw"<<endl;break;
                    }
                    cout<<"\n\n Enter the location in the form of x and y (ex: 1,1)\n";
                }
            }
            else
            {
                cout<<"\t\t\t TIC TAC TOE by Bhaskar Nihaal\n\n\n";
                for(int i=1;i<=3;i++)
                    for(int j=1;j<=3;j++)
                        board[i][j]='-';
                print();
                cout<<"\n\n Enter the location in the form of x and y (ex: 1,1)\n";
                int x,y;
                while(1)
                {
                    cin>>x>>y;
                    if(board[x][y]!='-'||x<1||x>3||y<1||y>3)
                    {
                        cout<<"Enter valid move"<<endl;continue;
                    }
                    if(turn==0)
                        board[x][y]='X';
                    else
                        board[x][y]='O';
                    system("cls");
                    cout<<"\t\t\t TIC TAC TOE by Bhaskar Nihaal\n\n\n";
                    print();
                    int result=isgameover();
                    turn=1-turn;
                    if(result==1)
                    {
                        if(turn==1)
                            cout<<"Congratulations Player 1 wins"<<endl;
                        else
                            cout<<"Congratulations Player 2 wins"<<endl;
                        break;
                    }
                    else if(result==-1)
                    {
                        cout<<"Draw"<<endl;break;
                    }
                    cout<<"\n\n Enter the location in the form of x and y (ex: 1,1)\n";
                }

            }
            //system("cls");
        }
        cout<<"1:play game 2:instructions 3:exit"<<endl;
        turn=0;
    }
    return 0;
}
