// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT1L 
// Names: MUHAMAD SYAMIL IMRAN BIN MOHD MANSOR | MUHAMMAD AMMAR AJWAD |
// IDs: 1221303708 | 1211303991 |
// Emails: syamil.imran.m@gmail.com | 1211303991@student.mmu.edu.my |
// Phones: +601110179892 | +60182606324 |
// ********************************************************* 

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

class GameBoard 
{
private:
    vector< vector<char> > map_;  
    int dimX_, dimY_;             

public:

    GameBoard(int dimX = 9, int dimY = 5);
    int noOfZombies = 2;
    void init(int dimX, int dimY);
    void display() const;
    void SettingsDisplay(int dimX, int dimY);
    void setObject(int x, int y, char ch);

    int getNoOfZombies();
    int getDimX() const;
    int getDimY() const;
    bool isEmpty(int x, int y);
    bool isInsideMap(int x, int y);

};

GameBoard::GameBoard(int dimX, int dimY)
{
    dimX_ = dimX;
    dimY_ = dimY;
    SettingsDisplay(dimX_, dimY_);
    init(dimX_, dimY_);
}

void GameBoard::SettingsDisplay(int dimX, int dimY)
{
    char decision;
    cout << "Default Game Settings" << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows     : " << dimY << endl;
    cout << "Board Columns  : " << dimX << endl;
    cout << "Zombie Count   : " << noOfZombies << endl << endl;

    cout << "Do you wish to change the game settings? (y/n)? => ";
    cin >> decision;

    system("CLS");

    switch (decision)
    {
        case 'y':
        cout << "Board settings" << endl;
        cout << "----------------" << endl;
        cout << "Enter rows => ";
        cin >> dimY_;
            while (dimY_ % 2 == 0)
            {
                cout << "Value must be an odd number, please re-enter => ";
                cin >> dimY_;
            } 
        cout << "Enter columns => ";
        cin >> dimX_;
            while (dimX_ % 2 == 0)
            {
                cout << "Value must be an odd number, please re-enter => ";
                cin >> dimX_;
            }
        cout << endl << "Zombie settings" << endl;
        cout << "----------------" << endl;
        cout << "Enter number of Zombies => ";
        cin >> noOfZombies;
            while (noOfZombies > 9)
            {
                cout << "Value must be an below 9, please re-enter => ";
                cin >> noOfZombies;
            } 
        cout << endl << "Settings Updated." << endl;
        system("pause");
        system("cls");
        break;
        case 'n':
        break;
    }
}


void GameBoard::init(int dimX, int dimY)
{

    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'h', 'v', '^', '>', '<', 'p', 'r'};
    int noOfObjects = 14;

    
    map_.resize(dimY_); 
    for (int i = 0; i < dimY_; ++i)
    {
        map_[i]. resize(dimX_);
    }

    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
}

void GameBoard::display() const
{

    // system("cls"); // OR system("clear"); for Linux / MacOS
    if (dimX_ > 10)
    {
        for (int i = 1; i < dimX_-10; i++)
        {
            cout << " ";
        }
    }

    cout << "  .: Alien vs Zombie :." << endl;

    // for each row
    for (int i = 0; i < dimY_; ++i)
    {
        // display upper border of the row
        cout << "  ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;

        // display row number
        cout << setw(2) << (i+1);

        // display cell content and border of each column
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }

    // display lower border of the last row
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;

    // display column number
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl << endl;
}

int GameBoard::getDimX() const
{
    return dimX_;
}

int GameBoard::getDimY() const
{
    return dimY_;
}

bool GameBoard::isEmpty(int x,int y)
{
    return map_[y-1][x-1] == ' ';
}

bool GameBoard::isInsideMap(int x,int y)
{
    return (0 < x && x <= dimX_) && (0 < y && y <= dimY_);
} 

void GameBoard::setObject(int x, int y, char ch)
{
    map_[y-1][x-1] = ch;
}

int GameBoard::getNoOfZombies()
{
    return noOfZombies;
}

class Characters
{
    private:
    int number;
    int x_, y_;
    char icon; 
    int life_;
    int att_;
    int range_;
    string Command_ = "up";

    public:
    Characters(char icon);
    void attributes(int life, int att, int range);
    void spawnInMiddle(GameBoard &gameboard);
    void spawnRandom(GameBoard &gameboard);
    void displayAlien();
    void displayZombies(int i, int num);
    string getCommand();
    void Command(GameBoard &gameboard);
};

Characters::Characters(char symbol)
{
    icon = symbol;
}

void Characters::attributes(int life, int att, int range)
{
    life_ = life;
    att_ = att;
    range_ = range;
}

void Characters::spawnInMiddle(GameBoard &gameboard)
{

    x_ = (gameboard.getDimX() / 2) + 1;
    y_ = (gameboard.getDimY() / 2) + 1;

    gameboard.setObject(x_, y_, icon);
}

void Characters::spawnRandom(GameBoard &gameboard)
{

    x_ = (1 + rand() % gameboard.getDimX());
    y_ = (1 + rand() % gameboard.getDimY());

    if (x_ == (gameboard.getDimX() / 2) + 1 || y_ == (gameboard.getDimY() / 2) + 1)
    {
        x_ = (1 + rand() % gameboard.getDimX());
        y_ = (1 + rand() % gameboard.getDimY());
    }

    gameboard.setObject(x_, y_, icon);
} 

void game()
{
    GameBoard gameboard;
    Characters alien('A');
    alien.attributes(100, 0, 1);
    vector<Characters> zombies;

    alien.spawnInMiddle(gameboard);
    
    for (int i = 0; i < gameboard.noOfZombies; i++)
    {
        char ch = i + 1 + '0';
        zombies.push_back(Characters(ch));
        zombies[i].spawnRandom(gameboard);
        zombies[i].attributes((10 + rand() % 30) * 10 , (1 + rand() % 6) * 5 , 1 + rand() % 5);
    }

        gameboard.display();
        alien.displayAlien();
        for (int i = 0; i < gameboard.noOfZombies; i++)
        zombies[i].displayZombies(i, gameboard.noOfZombies);

        alien.getCommand();
        int k;
        cin >> k;
        do {
            alien.Command(gameboard);
            gameboard.display();
            alien.displayAlien();
            for (int i = 0; i < gameboard.noOfZombies; i++)
            zombies[i].displayZombies(i, gameboard.noOfZombies);
        } while(alien.getCommand() == "up");
}

void Characters::displayAlien()
{
    cout << "Alien       : Life " << setw(3) << life_ << ", Attack :  " << setw(2) << att_ << endl; 
}

void Characters::displayZombies(int i, int num)
{
    cout << "Zombie " << i+1 << "    : Life " << setw(3) << life_ << ", Attack :  " << setw(2) << att_ << ", Range : " << range_ << endl; 
}

string Characters::getCommand()
{
    string command = Command_;
    return command;
}

void Characters::Command(GameBoard &gameboard)
{

    if (Command_ == "up")
    {
        gameboard.setObject(x_, y_, '.');
        gameboard.setObject(x_, y_-1, icon);
        y_ = y_-1;
    }
    else if (Command_ == "down")
    {
        gameboard.setObject(x_, y_, '.');
        gameboard.setObject(x_, y_+1, icon);
        y_ = y_+1;
    }
    else if (Command_ == "left")
    {
        gameboard.setObject(x_, y_, '.');
        gameboard.setObject(x_-1, y_, icon);
        x_ = x_-1;
    }
    else if (Command_ == "right")
    {
        gameboard.setObject(x_, y_, '.');
        gameboard.setObject(x_+1, y_, icon);
        x_ = x_+1;
    }
}

int main()
{
    game();
    system("pause");
}