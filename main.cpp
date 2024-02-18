#include <iostream>



void print_board(char board[3][3])
{
    for (short row = 0; row < 3; row ++)
    {
        std::cout << "   |   |" << std::endl;

        for (short column = 0; column < 3; column++)
        {
            std::cout << " " << board[row][column];

            if (column != 2)
                std::cout << " |";
        }
            
        std::cout << std::endl << "   |   |" << std::endl;

        if (row != 2)
            std::cout << "-----------" << std::endl;
    }

    std::cout << std::endl << std::endl;
}



//This function returns true if there are moves remaining, else it return false
bool are_moves_left(char board[3][3])
{
    for (short row = 0; row < 3 ; row ++)
        for (short column = 0; column < 3; column ++)
            if (board[row][column] != 'X' && board[row][column] != 'O')
                return true;

    return false;
}



short evaluate_board(char board[3][3])
{
    // Checking on rows
    for (short row = 0; row < 3; row ++)
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
        {
            if (board[row][0] == 'X')
                return -10;
            else
                return 10;
        }


    // Checking on columns
    for (short column = 0; column < 3; column ++)
        if (board[0][column] == board[1][column] && board[1][column] == board[2][column])
        {
            if (board[0][column] == 'X')
                return -10;
            else
                return 10;
        }


    // Checking main diagonal
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == 'X')
            return -10;
        else
            return 10;
    }

    
    // Checking antidiagonal
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == 'X')
            return -10;
        else
            return 10;
    }

    return 0;
}



short minimax(char board[3][3], short depth, bool is_maximizing_player)
{
    short score = evaluate_board(board);

    if (score == -10 || score == 10)
        return score;
    
    if (!are_moves_left(board))
        return 0;
    
    if (is_maximizing_player)
    {
        short best = -1000;

        for (short row = 0; row < 3; row ++)
            for (short column = 0; column < 3; column ++)
                if (board[row][column] != 'X' && board[row][column] != 'O')
                {   
                    char board_value = board[row][column];
                    board[row][column] = 'O';
                    best = std::max(best, minimax(board, depth + 1, !is_maximizing_player));
                    board[row][column] = board_value;
                }
        
        return best;
    }

    else
    {
        short best = 1000;

        for (short row = 0; row < 3; row ++)
            for (short column = 0; column < 3; column ++)
                if (board[row][column] != 'X' && board[row][column] != 'O')
                {
                    char board_value = board[row][column];
                    board[row][column] = 'X';
                    best = std::min(best, minimax(board, depth + 1, !is_maximizing_player));
                    board[row][column] = board_value;
                }
        
        return best;
    }
}



void find_best_move(char board[3][3], short best_move[2])
{
    short best_value = -1000;

    for (short row = 0; row < 3; row ++)
        for (short column = 0; column < 3; column ++)
            if (board[row][column] != 'X' && board[row][column] != 'O')
            {
                char board_value = board[row][column];
                board[row][column] = 'O';
                short move_value = minimax(board, 0, false);
                board[row][column]= board_value;

                if (move_value > best_value)
                {
                    best_move[0] = row;
                    best_move[1] = column;
                    best_value = move_value;
                }
            }
}


void move_player(char board[3][3])
{
    short position;

    std::cout << "Position: ";
    std::cin >> position;

    if (position <= 3)
        board[0][position - 1] = 'X';
    
    else if (position > 3 && position <= 6)
        board[1][position - 4] = 'X';
    
    else
        board[2][position - 7] = 'X';
    
    std::cout << std::endl;
}



int main(void)
{
    char board[3][3] = {{'1', '2', '3'},
                        {'4', '5', '6'},
                        {'7', '8', '9'}};
    short o_move[2];

    std::cout << std::endl << std::endl << "Welcome!" << std::endl;
    std::cout << "You will move first. You are with X." << std::endl;
    std::cout << "The game board has positions numbered from 1 to 9." << std::endl << std::endl;

    while(1)
    {
        print_board(board);

        if (evaluate_board(board) == -10)
        {
            std::cout << "You won. Congratulations!" << std::endl << std::endl;
            break;
        }
        else if (evaluate_board(board) == 10)
        {
            std::cout << "You lost. Try again." << std::endl << std::endl;
            break;
        }

        if (!are_moves_left(board))
        {
            std::cout << "Draw!" << std::endl << std::endl;
            break;
        }

        move_player(board);

        find_best_move(board, o_move);

        board[o_move[0]][o_move[1]] = 'O';
    }

    return 0;
}