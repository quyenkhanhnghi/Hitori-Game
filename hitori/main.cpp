/* Hitori
 *
 * Desc:
 *   This program implements a Hitori game with the game board of
 * size 5 x 5. Each square in the game board has a number from 1-5.
 * At first, each horizontal and vertical row can have several identical
 * numbers, but the purpose is to remove numbers such that each horizontal
 * and vertical row has no duplicate numbers. However, it is not possible
 * to remove numbers in adjacent squares, and none of the remaining
 * numbers (squares) can be isolated from the other ones, i.e. it is not
 * possible to remove all numbers around it (from strictly above, below,
 * left, right).
 *   At first, the user is asked, if the game board will be filled with
 * randomly drawn numbers 1-5, or with user-given 25 numbers. In the first
 * option, a seed value for the random number generator will be asked next.
 * In the latter option, the user is asked to input 25 numbers.
 *   On each round, the user is asked for coordinates, i.e. two numbers.
 * The player wins if each horizantal and vertical row has at most one
 * instance of each number 1-5. The player loses if they remove a number,
 * the adjacent number of which has already been removed or if a number
 * becomes isolated.
 *   The program checks the user-given coordinates. They must be inside the
 * game board, and the square indicated by them must have a number, i.e.
 * a number cannot be removed again.
 *   When the game ends, the program tells if the player won or lost.
 *
 * Program author 
 * Name: Quyen Khanh Nghi
 * Student number: 150502225
 * UserID: cnngqu 
 * E-Mail: nghi.quyen@tuni.fi
 * 
 * Name: Tran Van Anh
 * Student number: 150511795
 * E-Mail: anh.v.tran@tuni.fi
 *
 * Notes about the program and it's implementation:
 * The program split 2 main part: fill the board and check win/lost condition
 * from user inputs'coordinates
 * The program uses vector in vector to store the coordination in board. 
 * Each step in the program is commented on in a detailed way

 * */

#include <iostream>
#include <vector>
#include <set>

using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';

const vector<int> offSetX {0, 1, -1, 0}; //parameter vector to calculate up and down 
                                         //positions according to X
const vector<int> offSetY {1, 0, 0, -1}; //parameter vector to calculate up and down 
                                         //positions according to Y

// Muuttaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan.
//
// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns zero.

unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Tulostaa pelilaudan rivi- ja sarakenumeroineen.
//
// Prints the game board with row and column numbers.
void print(const vector<vector<int>> & gameboard)
{
    cout << "=================" << endl;
    cout << "|   | 1 2 3 4 5 |" << endl;
    cout << "-----------------" << endl;
    for(unsigned int i = 0; i < BOARD_SIDE; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < BOARD_SIDE; ++j)
        {
            if(gameboard.at(i).at(j) == 0)
            {
                cout << EMPTY << " ";
            }
            else
            {
                cout << gameboard.at(i).at(j) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "=================" << endl;
}

// losing condition 1: adjacent square (of removed pos) is empty
bool empty_adjacent_square(const vector<vector<int>>& board, int x, int y) {

    for (unsigned int i = 0; i < offSetX.size(); i++)
    {
        int crrX = x + offSetX[i]; //calculate adjacent positions to check
        int crrY = y + offSetY[i];

        // targeted postion is at the corner of board
        // there's no left/right/up/down pos to consider -> check other pos
        if (crrX < 0 || crrX > 4 || crrY < 0 || crrY > 4) 
        { 
            continue;

        // adjacent pos is empty -> lose
        } else if (board.at(crrX).at(crrY) == 0) {
            return true;
        }
        
    }
    return false; // all adjacent pos are NOT empty
}

// losing condition 2: there is an isolated position (left/right/up/down positions of 
// that pos are ALL empty)
// step 1: check if a postion is isolated
bool is_isolated(vector<vector<int>> &board, int x, int y) {

    for (unsigned int i = 0; i < offSetX.size(); i++)
    {
        int crrX = x + offSetX[i]; //calculate adjacent pos to check
        int crrY = y + offSetY[i];

        // targeted postion is at the corner of board
        // there's no left/right/up/down pos to consider -> check other pos
        if (crrX < 0 || crrX > 4 || crrY < 0 || crrY > 4)
        {
            continue;

        // 1 of 4 adjacent positions is NOT empty -> not isolated 
        } else if (board.at(crrX).at(crrY) != 0) {
            return false;
        }
    }
    return true; // ALL 4 adjacent postitions are empty -> isolated pos
}

// step 2: check if the board has an isolated postion by checking 
// every postion in the board if it's isolated
bool have_isolated(vector<vector<int>> &board, int x, int y) 
{
    for (unsigned int i = 0; i < offSetX.size(); i++)
    {
        int crrX = x + offSetX[i];
        int crrY = y + offSetY[i];

        if (crrX < 0 || crrX > 4 || crrY < 0 || crrY > 4)
        {
            continue;
    
        // if there is an isolated position in the board 
        } else if (is_isolated(board, crrX, crrY)) {
            return true;
        }
    }
    return false; // there is NO isolated pos in the board
}
bool check_won(vector<vector<int>> &board) 
{
    set<int> check_row;
    set<int> check_column;
    for (unsigned int i = 0; i < BOARD_SIDE; i++) {
        for (unsigned int j = 0; j < BOARD_SIDE; j++) {
            if (board[i][j] == 0) {
                continue;
            }
            if (check_row.find(board[i][j]) != check_row.end()) {
                return false;
            } else {
                check_row.insert(board[i][j]);
            }
        }

        for (unsigned int j = 0; j < BOARD_SIDE; j++) {
            if (board[j][i] == 0) {
                continue;
            }
            if (check_column.find(board[j][i]) != check_column.end()) {
                return false;
            } else {
                check_column.insert(board[j][i]);
            }
        }

        check_row.clear();
        check_column.clear();
    }

    return true;
}

void read_input(vector<vector<int>> &board)
{
    string mode;

    // fill in the board
    while (true) {
        cout << "Select start (R for random, I for input): ";
        getline(cin, mode);

        if (mode == "r" || mode == "R") 
        {
            int seed = 0;
            cout << "Enter seed value: ";
            cin >> seed;
            srand(seed);

            for (unsigned int i = 0; i < BOARD_SIDE; i++) // rows
            {
                for (unsigned int j = 0; j < BOARD_SIDE; j++) // columns
                {
                    board[i][j] = 1 + rand() % 5;
                }
            }
                    
            break;
        }
        
        if (mode == "i" || mode == "I") 
        {
            int temp = 0;
         
            cout << "Input: ";

            for (unsigned int i = 0; i < BOARD_SIDE; i++)
            {
                for (unsigned int j = 0; j < BOARD_SIDE; j++) 
                {
                    cin >> temp;
                    board[i][j] = temp;
                }
            }
            break;
        }
    }

}

void check_case(vector<vector<int>> &board) 
{
    string coords = "";
   

    cin.ignore();   
    while (true) {
        
        print(board);

        int x = 0, y = 0;

        while (true) {
            cout << "Enter removable element (x, y): ";
            
            string cmd1, cmd2;

            // take inputs
            cin >> cmd1;
            if (cmd1 == "q") {
                cout << "Quitting";
                return;
            }
            cin >> cmd2;

            // Change x-y coordinates due to given board
            x = stoi_with_check(cmd2);
            y = stoi_with_check(cmd1);

            // Out of board condition -> take different input
            if (x == 0 || x > 5 || y > 5 || y == 0) {
                cout << "Out of board" << endl;
                continue;
            } 
            else 
            {
                // calculate index of element in the board
                x -= 1;
                y -= 1;
                
                // That pos is removed -> take different input
                if (board[x][y] == 0) {
                    cout << "Already removed" << endl;
                    continue;
                }
                break;
            }
        }
        
        // when the input element is removable
	    // remove element by setting pos = 0
        board[x][y] = 0;

        // check losing conditions
        if (empty_adjacent_square(board, x, y) || have_isolated(board,x,y)) {
            print(board);
            cout << "You lost" << endl;
            break;
        }
        
        // if not losing, continue to check winning condition
        if (check_won(board)) {
            print(board);
            cout << "You won" << endl;
            break;
        }

    }
}

int main()
{
    // Datastructure to store the board
    vector<vector<int>> board (BOARD_SIDE, vector<int>(BOARD_SIDE, 0));
    read_input(board); // Read input from user to fill the board
    check_case(board); // Check win or lost condition
    return 0;
}
