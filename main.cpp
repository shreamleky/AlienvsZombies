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
    char checkobstacle(int x, int y);

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

char GameBoard::checkobstacle(int x, int y)
{
    return map_[y-1][x-1];
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

    public:
    Characters(char icon);
    int getLife();
    void attributes(int life, int att, int range);
    void spawnInMiddle(GameBoard &gameboard);
    void spawnRandom(GameBoard &gameboard);
    void displayAlien();
    void displayZombies(int i, int num);
    void Command(GameBoard &gameboard, vector<Characters> zombies);
    void MoveUp(GameBoard &gameboard);
    void MoveDown(GameBoard &gameboard);
    void MoveLeft(GameBoard &gameboard);
    void MoveRight(GameBoard &gameboard);
    void Arrow();
    void Health();
    void Rock(int x, int y, GameBoard &gameboard);
    void Empty(GameBoard &gameboard);
    void Pod(GameBoard &gameboard, vector<Characters> zombies);

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

int Characters::getLife()
{
    int life = life_;
    return life;
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

    while (alien.getLife() > 0){
        gameboard.display();
        alien.displayAlien();
        for (int i = 0; i < gameboard.noOfZombies; i++)
        zombies[i].displayZombies(i, gameboard.noOfZombies);

        alien.Command(gameboard, zombies);
        alien.displayAlien();
        for (int i = 0; i < gameboard.noOfZombies; i++)
        zombies[i].displayZombies(i, gameboard.noOfZombies);
        system("pause");
        system("CLS");
    } 
}

void Characters::displayAlien()
{
    cout << "Alien       : Life " << setw(3) << life_ << ", Attack :  " << setw(2) << att_ << endl; 
}

void Characters::displayZombies(int i, int num)
{
    cout << "Zombie " << i+1 << "    : Life " << setw(3) << life_ << ", Attack :  " << setw(2) << att_ << ", Range : " << range_ << endl; 
}

void Characters::MoveUp(GameBoard &gameboard)
{
    gameboard.setObject(x_, y_, '.');
    gameboard.setObject(x_, y_-1, icon);
    y_ = y_-1;
    gameboard.display();

}

void Characters::MoveDown(GameBoard &gameboard)
{
    gameboard.setObject(x_, y_, '.');
    gameboard.setObject(x_, y_+1, icon);
    y_ = y_+1;
    gameboard.display();

}

void Characters::MoveLeft(GameBoard &gameboard)
{
    gameboard.setObject(x_, y_, '.');
    gameboard.setObject(x_-1, y_, icon);
    x_ = x_-1;
    gameboard.display();

}

void Characters::MoveRight(GameBoard &gameboard)
{
    gameboard.setObject(x_, y_, '.');
    gameboard.setObject(x_+1, y_, icon);
    x_ = x_+1;
    gameboard.display();
    
}

void Characters::Command(GameBoard &gameboard, vector<Characters> zombies)
{
    string Command;
    cout << endl << "command> ";
    cin >> Command;
    start:;

    if (Command == "up")
    {
        while (gameboard.isInsideMap(x_, y_-1))
        {
            switch (gameboard.checkobstacle(x_, y_-1))
            {
                case ' ':
                    Empty(gameboard);
                    break;
                case 'r':
                    Rock(x_, y_-1, gameboard);  
                    gameboard.display();
                    goto endOfupLoop;
                    break;
                case 'h':
                    Health();
                    break;
                case 'p':
                    Pod(gameboard, zombies);
                    break;
                case '^':
                    Arrow();                   
                    break;
                case 'v':
                    Arrow();
                    Command = "down";
                    MoveUp(gameboard);
                    system("pause");
                    system("CLS");
                    goto start;
                    break;
                case '<':
                    Arrow();
                    Command = "left";
                    MoveUp(gameboard);
                    system("pause");
                    system("CLS");
                    goto start;
                    break;
                case '>':
                    Arrow();
                    Command = "right";
                    MoveUp(gameboard);
                    system("pause");
                    system("CLS");
                    goto start;
                    break;
                default:
                    break;
            }   
            MoveUp(gameboard);
        }
        endOfupLoop:;
    }
    else if (Command == "down")
    {
        while (gameboard.isInsideMap(x_, y_+1))
        {
            switch (gameboard.checkobstacle(x_, y_+1))
            {
                case ' ':
                    Empty(gameboard);
                    break;
                case 'r':
                    Rock(x_, y_+1, gameboard);  
                    gameboard.display();
                    goto endOfdownLoop;
                    break;
                case 'h':
                    Health();
                    break;
                case 'p':
                    Pod(gameboard, zombies);
                    break;
                case '^':
                    Arrow();
                    Command = "up";
                    MoveDown(gameboard);
                    system("pause");
                    system("CLS");
                    goto start;
                    break;
                case 'v':
                    Arrow();
                    break;
                case '<':
                    Arrow();
                    Command = "left";
                    MoveDown(gameboard);
                    system("pause");
                    system("CLS");
                    goto start;
                    break;
                case '>':
                    Arrow();
                    Command = "right";
                    MoveDown(gameboard);
                    system("pause");
                    system("CLS");
                    goto start;
                    break;
                default:
                    break;
            }   
            MoveDown(gameboard);
        }
        endOfdownLoop:;
    }
    else if (Command == "left")
    {
        while (gameboard.isInsideMap(x_-1, y_))
        {
            switch (gameboard.checkobstacle(x_-1, y_))
            {
                case ' ':
                    Empty(gameboard);
                    break;
                case 'r':
                    Rock(x_-1, y_, gameboard) ; 
                    gameboard.display();
                    goto endOfleftLoop;
                    break;
                case 'h':
                    Health();
                    break;
                case 'p':
                    Pod(gameboard, zombies);
                    break;
                case '^':
                    Arrow();
                    Command = "up";
                    MoveLeft(gameboard);
                    system("pause");
                    system("CLS");
                    goto start;
                    break;
                case 'v':
                    Arrow();
                    Command = "down";
                    MoveLeft(gameboard);
                    system("pause");
                    system("CLS");
                    goto start;
                    break;
                case '<':
                    Arrow();
                    break;
                case '>':
                    Arrow();
                    Command = "right";
                    MoveLeft(gameboard);
                    system("pause");
                    system("CLS");
                    goto start;
                    break;
                default:
                    break;
            }   
            MoveLeft(gameboard);
        }
        endOfleftLoop:;
    }
    else if (Command == "right")
    {
        while (gameboard.isInsideMap(x_+1, y_))
        {
            switch (gameboard.checkobstacle(x_+1, y_))
            {
                case ' ':
                    Empty(gameboard);
                    break;
                case 'r':
                    Rock(x_+1, y_, gameboard);  
                    gameboard.display();
                    goto endOfrightLoop;
                    break;
                case 'h':
                    Health();
                    break;
                case 'p':
                    Pod(gameboard, zombies);
                    break;
                case '^':
                    Arrow();
                    Command = "up";
                    MoveRight(gameboard);
                    system("pause");
                    system("CLS");
                    goto start;
                    break;
                case 'v':
                    Arrow();
                    Command = "down";
                    MoveRight(gameboard);
                    system("pause");
                    system("CLS");
                    goto start;
                    break;
                case '<':
                    Arrow();
                    Command = "left";
                    MoveRight(gameboard);
                    system("pause");
                    system("CLS");
                    goto start;
                    break;
                case '>':
                    Arrow();
                    break;
                default:
                    break;
            }   
            MoveRight(gameboard);
        }
        endOfrightLoop:;
    }
    else if (Command == "quit")
    {
        exit(1);
    }

}

void Characters::Arrow()
{
    cout << "Alien finds an arrow." << endl;
    cout << "Alien's attack is increased by 20." << endl << endl;
    system("pause");
    system("CLS");
    att_ += 20;
}

void Characters::Health()
{
    cout << "Alien finds a health pack." << endl;
    cout << "Alien's life is increased by 20." << endl << endl;
    system("pause");
    system("CLS");
    life_ += 20;
}

void Characters::Pod(GameBoard &gameboard, vector<Characters> zombies)
{
    cout << "Alien finds a pod." << endl << endl;
    for (int i = 0; i < gameboard.noOfZombies; i++)
    zombies[i].life_ -= 10;

    system("pause");
    system("CLS");
}

void Characters::Rock(int x, int y, GameBoard &gameboard)
{
    char objects[] = {'h', 'v', '^', '>', '<', 'p'};
    int noOfObjects = 6;
    int objNo = rand() % noOfObjects;

    cout << "Alien stumbles upon a rock." << endl;
    gameboard.setObject(x, y, objects[objNo]);
    switch (objects[objNo])
    {
    case 'h':
        cout << "Alien discovers a health pack beneath the rock." << endl;
        system("pause");
        system("CLS");
        break;
    case 'v':
    case '^': 
    case '>':
    case '<':
        cout << "Alien discovers an arrow beneath the rock." << endl;
        system("pause");
        system("CLS");
        break;
    case 'p':
        cout << "Alien discovers a pod beneath the rock." << endl;
        system("pause");
        system("CLS");
        break;
    default:
        break;
    }
}

void Characters::Empty(GameBoard &gameboard)
{
    cout << "Alien finds an empty space." << endl;
    system("pause");
    system("CLS");
}






int main()
{
    game();
    system("pause");
}