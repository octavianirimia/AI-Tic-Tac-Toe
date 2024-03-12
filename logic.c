short max(short a, short b)
{
  return (a > b) ? a : b;
}



short min(short a, short b)
{
    return (a < b) ? a : b;
}



char is_cell_empty(const char board[3][3], const unsigned short position[2])
{
    if (board[position[0]][position[1]] == ' ')
        return 't';

    return 'f';
}



//This function returns true if there are moves remaining, else it return false
char are_moves_left(const char board[3][3])
{
    for (unsigned short row = 0; row < 3 ; row ++)
        for (unsigned short column = 0; column < 3; column ++)
            if (board[row][column] == ' ')
                return 't';

    return 'f';
}



short evaluate_board(const char board[3][3])
{
    // Checking on rows
    for (unsigned short row = 0; row < 3; row ++)
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
        {
            if (board[row][0] == 'X')
                return -10;
            else if (board[row][0] == 'O')
                return 10;
        }


    // Checking on columns
    for (unsigned short column = 0; column < 3; column ++)
        if (board[0][column] == board[1][column] && board[1][column] == board[2][column])
        {
            if (board[0][column] == 'X')
                return -10;
            else if(board[0][column] == 'O')
                return 10;
        }


    // Checking main diagonal
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == 'X')
            return -10;
        else if (board[0][0] == 'O')
            return 10;
    }

    
    // Checking antidiagonal
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == 'X')
            return -10;
        else if (board[0][2] == 'O')
            return 10;
    }

    return 0;
}



short minimax(char board[3][3], unsigned short depth, unsigned short is_maximizing_player, short alpha, short beta)
{
    short score = evaluate_board(board);

    if (score == -10 || score == 10 || are_moves_left(board) == 'f')
        return score;

    if (is_maximizing_player)
    {
        short best = -1000;

        for (short row = 0; row < 3; row ++)
            for (short column = 0; column < 3; column ++)
                if (board[row][column] == ' ')
                {   
                    board[row][column] = 'O';
                    best = max(best, minimax(board, depth + 1, !is_maximizing_player, alpha, beta));
                    board[row][column] = ' ';

                    alpha = max(alpha, best);
                    if (alpha >= beta)
                        break;
                }
        
        return best;
    }

    else
    {
        short best = 1000;

        for (short row = 0; row < 3; row ++)
            for (short column = 0; column < 3; column ++)
                if (board[row][column] == ' ')
                {
                    board[row][column] = 'X';
                    best = min(best, minimax(board, depth + 1, !is_maximizing_player, alpha, beta));
                    board[row][column] = ' ';

                    beta = min(beta, best);
                    if (alpha >= beta)
                        break;
                }
        
        return best;
    }
}



void find_best_move(char board[3][3], unsigned short best_move[2])
{
    short best_value = -1000;

    for (unsigned short row = 0; row < 3; row ++)
        for (unsigned short column = 0; column < 3; column ++)
            if (board[row][column] == ' ')
            {
                board[row][column] = 'O';
                short move_value = minimax(board, 0, 0, -1000, 1000);
                board[row][column]= ' ';

                if (move_value > best_value)
                {
                    best_move[0] = row;
                    best_move[1] = column;
                    best_value = move_value;
                }
            }
}



void move_player(char board[3][3], const unsigned short x_move[2])
{
    if (is_cell_empty(board, x_move) == 't')
        board[x_move[0]][x_move[1]] = 'X';
}



unsigned short logic (char board[3][3], unsigned short x_move[2], unsigned short o_move[2])
{
    move_player(board, x_move);

    find_best_move(board, o_move);

    board[o_move[0]][o_move[1]] = 'O';

    if (evaluate_board(board) == -10)
        return 0;

    else if (evaluate_board(board) == 10)
        return 1;

    else if (are_moves_left(board) == 'f')
        return 2;

    return 3;
}