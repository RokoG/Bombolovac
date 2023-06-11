#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>

using namespace std;

const int MAX_BOARD_SIZE = 10;
const char HIDDEN = '#';
const char MINE = '*';

char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
bool revealed[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
bool flagged[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int boardSize;
int numMines;

void initializeBoard()
{
    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            board[i][j] = HIDDEN;
            revealed[i][j] = false;
            flagged[i][j] = false;
        }
    }
}

void placeMines(int numMines)
{
    int count = 0;
    while (count < numMines)
    {
        int x = rand() % boardSize;
        int y = rand() % boardSize;

        if (board[x][y] != MINE)
        {
            board[x][y] = MINE;
            ++count;
        }
    }
}

void displayBoard()
{
    cout << endl;
    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            if (revealed[i][j])
            {
                cout << board[i][j] << ' ';
            }
            else if (flagged[i][j])
            {
                cout << "F ";
            }
            else
            {
                cout << HIDDEN << ' ';
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool isValidPosition(int x, int y)
{
    return (x >= 0 && x < boardSize && y >= 0 && y < boardSize);
}

void revealCell(int x, int y)
{
    if (!isValidPosition(x, y) || revealed[x][y] || flagged[x][y])
    {
        return;
    }

    revealed[x][y] = true;

    if (board[x][y] == MINE)
    {
        cout << "Game over! You hit a mine." << endl;
        return;
    }

    int count = 0;
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            int nx = x + dx;
            int ny = y + dy;

            if (isValidPosition(nx, ny) && board[nx][ny] == MINE)
            {
                ++count;
            }
        }
    }

    if (count > 0)
    {
        board[x][y] = '0' + count;
    }
    else
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                int nx = x + dx;
                int ny = y + dy;

                if (isValidPosition(nx, ny) && !revealed[nx][ny])
                {
                    revealCell(nx, ny);
                }
            }
        }
    }
}

void flagCell(int x, int y)
{
    if (isValidPosition(x, y))
    {
        flagged[x][y] = !flagged[x][y];
    }
}

bool isGameOver()
{
    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            if (!revealed[i][j] && board[i][j] != MINE)
            {
                return false;
            }
        }
    }
    return true;
}

void saveGame(const string& filename)
{
    ofstream file(filename, ios::binary);

    file.write(reinterpret_cast<const char*>(&boardSize), sizeof(boardSize));
    file.write(reinterpret_cast<const char*>(board), sizeof(board));
    file.write(reinterpret_cast<const char*>(revealed), sizeof(revealed));
    file.write(reinterpret_cast<const char*>(flagged), sizeof(flagged));

    file.close();

    cout << "Game saved successfully." << endl;
}

void loadGame(const string& filename)
{
    ifstream file(filename, ios::binary);

    if (!file)
    {
        cout << "Failed to open file." << endl;
        return;
    }

    file.read(reinterpret_cast<char*>(&boardSize), sizeof(boardSize));
    file.read(reinterpret_cast<char*>(board), sizeof(board));
    file.read(reinterpret_cast<char*>(revealed), sizeof(revealed));
    file.read(reinterpret_cast<char*>(flagged), sizeof(flagged));

    file.close();

    cout << "Game loaded successfully." << endl;
}

void printMenu()
{
    cout << "Menu:" << endl;
    cout << "1. Reveal cell" << endl;
    cout << "2. Flag cell" << endl;
    cout << "3. Save game" << endl;
    cout << "4. Load game" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "Welcome to Minesweeper!" << endl;

    while (true)
    {
        cout << "Menu:" << endl;
        cout << "1. New Game" << endl;
        cout << "2. Load Game" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            string playerName;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, playerName);
            ofstream playerNameFile("player_name.txt");
            if (playerNameFile.is_open())
            {
                playerNameFile << playerName;
                playerNameFile.close();
                cout << "Player name saved successfully." << endl;
            }
            else
            {
                cout << "Failed to open player name file." << endl;
            }

            cout << "Enter the board size (4 - 10): ";
            cin >> boardSize;

            if (boardSize < 4 || boardSize > 10)
            {
                cout << "Invalid board size. Setting board size to 10." << endl;
                boardSize = 10;
            }

            cout << "Enter the number of mines: ";
            cin >> numMines;

            initializeBoard();
            placeMines(numMines);

            cout << "New game started. Good luck, " << playerName << "!" << endl;
        }
        else if (choice == 2)
        {
            string saveFile;
            cout << "Enter the filename to load: ";
            cin >> saveFile;
            loadGame(saveFile);
        }
        else if (choice == 3)
        {
            cout << "Goodbye!" << endl;
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }

        while (!isGameOver())
        {
            displayBoard();
            printMenu();

            cin >> choice;

            if (choice == 1)
            {
                int x, y;
                cout << "Enter the coordinates (x, y): ";
                cin >> x >> y;
                revealCell(x, y);
            }
            else if (choice == 2)
            {
                int x, y;
                cout << "Enter the coordinates (x, y): ";
                cin >> x >> y;
                flagCell(x, y);
            }
            else if (choice == 3)
            {
                string saveFile;
                cout << "Enter the filename to save: ";
                cin >> saveFile;
                saveGame(saveFile);
            }
            else if (choice == 4)
            {
                string loadFile;
                cout << "Enter the filename to load: ";
                cin >> loadFile;
                loadGame(loadFile);
            }
            else if (choice == 5)
            {
                cout << "Exiting the game..." << endl;
                break;
            }
            else
            {
                cout << "Invalid choice. Please try again." << endl;
            }
        }

        if (isGameOver())
        {
            cout << "Game over! You won!" << endl;
        }
    }

    return 0;
}

