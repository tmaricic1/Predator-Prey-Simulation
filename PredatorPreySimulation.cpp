#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Organism;
class Ant;
class Doodlebug;
class Grid;
class Empty;

class Organism {

    int x, y;
    bool movedThisRound;

public:

    Organism() { x = 0; y = 0; movedThisRound = false; }
    void setX(int xParameter) { x = xParameter; }
    int getX() { return x; }
    void setY(int yParameter) { y = yParameter; }
    int getY() { return y; }
    virtual void move(Grid& grid) = 0;
    virtual char getChar() = 0;
    void setMovedThisTurn(bool moved) { movedThisRound = moved; }
    bool getMovedThisTurn() { return movedThisRound; }
    virtual void breed(Grid& grid) = 0;
    virtual void dies(Grid& grid) = 0;

};

class Empty : public Organism {

    char emptyChar;
public:

    Empty() { emptyChar = '-'; }
    char getChar() { return emptyChar; }
    virtual void move(Grid& grid) {};
    virtual void breed(Grid& grid) {};
    virtual void dies(Grid& grid) {};

};

class Ant : public Organism {

    int antDaysAlive;
    char antChar;

public:

    Ant() { antDaysAlive = 0; antChar = 'o'; }
    Ant(int _x, int _y) {
        antDaysAlive = 0;
        antChar = 'o';
        this->setX(_x);
        this->setX(_y);
    }
    void setAntDaysAlive(int _antDaysAlive) { antDaysAlive = _antDaysAlive; }
    int getAntDaysAlive() { return antDaysAlive; }
    char getChar() { return antChar; }
    virtual void move(Grid& grid);
    virtual void breed(Grid& grid);
    virtual void dies(Grid& grid) {};
};

class DoodleBug : public Organism {

    int doodlebugDaysAlive;
    int daysWithoutEating;
    char doodleBugChar;

public:

    DoodleBug() { doodlebugDaysAlive = 0; daysWithoutEating = 0; doodleBugChar = 'X'; }
    DoodleBug(int _x, int _y) {
        doodlebugDaysAlive = 0;
        daysWithoutEating = 0;
        doodleBugChar = 'X';
        this->setX(_x);
        this->setX(_y);
    }
    void setDoodleBugDaysAlive(int _doodlebugDaysAlive) { doodlebugDaysAlive = _doodlebugDaysAlive; }
    int getDoodleBugDaysAlive() { return doodlebugDaysAlive; }
    int getDaysWithoutEating() { return daysWithoutEating; }
    char getChar() { return doodleBugChar; }
    virtual void move(Grid& grid);
    virtual void breed(Grid& grid);
    virtual void dies(Grid& grid);

};

class Grid {

    Organism* grid[20][20];
    int timeStepCounter;

public:

    Grid() {

        for (int i = 0; i < 20; i++)
            for (int j = 0; j < 20; j++)
                grid[i][j] = nullptr;

        timeStepCounter = 0;

    }

    void initializeWorld();

    void progressWorld();

    void printWorld() {

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++)
                cout << grid[i][j]->getChar() << " ";
            cout << endl;
        }

    }

    void incrementTime() { timeStepCounter++; }
    int getTimeStep() { return timeStepCounter; }
    bool spaceIsEmpty(int _x, int _y) const {
        if (_x >= 0 && _x <= 19 && _y >= 0 && _y <= 19)
            return grid[_x][_y]->getChar() == '-';
        else
            return false;
    }
    bool notBeyondBoundary(int _x, int _y) { return _x >= 0 && _x <= 19 && _y >= 0 && _y <= 19; }
    void setEmpty(int _x, int _y) { grid[_x][_y] = new Empty; }
    void setNewAnt(int _x, int _y) { grid[_x][_y] = new Ant; grid[_x][_y]->setX(_x); grid[_x][_y]->setY(_y); }
    void setNewDoodleBug(int _x, int _y) { grid[_x][_y] = new DoodleBug; grid[_x][_y]->setX(_x); grid[_x][_y]->setY(_y); }
    void setNull(int _x, int _y) { grid[_x][_y] = nullptr; }
    bool containsAnt(int _x, int _y) {
        return _x >= 0 && _x <= 19 && _y >= 0 && _y <= 19 && grid[_x][_y]->getChar() == 'o';
    }
    bool containsDoodleBug(int _x, int _y) {
        return _x >= 0 && _x <= 19 && _y >= 0 && _y <= 19 && grid[_x][_y]->getChar() == 'X';
    }
    void setNewCoordinates(int _x, int _y, Organism* org) { grid[_x][_y] = org; }
    char returnCharAtPosition(int _x, int _y) {
        if (_x >= 0 && _x <= 19 && _y >= 0 && _y <= 19)
            return grid[_x][_y]->getChar();
        else
            return ' ';
    }
};

int main()
{

    srand(time(0));

    Grid map;
    map.initializeWorld();
    map.printWorld();

    cout << "Press the enter key to enter the next time step";
    string nextTimeStep;
    getline(cin, nextTimeStep);
    while (nextTimeStep.length() == 0) {

        map.progressWorld();
        map.printWorld();
        cout << "Press the enter key to enter the next time step" << endl;
        cout << "World iteration #" << map.getTimeStep();
        getline(cin, nextTimeStep);

    }

    return 0;

}


void Grid::initializeWorld() {

    int ranX, ranY;

    for (int i = 0; i < 5; i++) {

        bool placed = false;

        while (!placed) {

            ranX = rand() % 20;
            ranY = rand() % 20;

            if (grid[ranX][ranY] == nullptr) {

                grid[ranX][ranY] = new DoodleBug(ranX, ranY);
                grid[ranX][ranY]->setX(ranX);
                grid[ranX][ranY]->setY(ranY);
                placed = true;

            }
        }

    }

    for (int i = 0; i < 100; i++) {

        bool placed = false;

        while (!placed) {

            ranX = rand() % 20;
            ranY = rand() % 20;

            if (grid[ranX][ranY] == nullptr) {

                grid[ranX][ranY] = new Ant(ranX, ranY);
                grid[ranX][ranY]->setX(ranX);
                grid[ranX][ranY]->setY(ranY);
                placed = true;

            }
        }
    }

    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            if (grid[i][j] == nullptr)
                grid[i][j] = new Empty;

}
void Ant::move(Grid& grid) {

    if (!getMovedThisTurn()) {
        int direction = rand() % 4 + 1;
        int newX = getX();
        int newY = getY();
        int oldX = getX();
        int oldY = getY();

        if (direction == 1 && grid.notBeyondBoundary(getX(), getY() - 1)) {

            newX = getX();
            newY = getY() - 1;

        }
        if (direction == 2 && grid.notBeyondBoundary(getX(), getY() + 1)) {

            newX = getX();
            newY = getY() + 1;

        }
        if (direction == 3 && grid.notBeyondBoundary(getX() - 1, getY())) {

            newX = getX() - 1;
            newY = getY();

        }
        if (direction == 4 && grid.notBeyondBoundary(getX() + 1, getY())) {

            newX = getX() + 1;
            newY = getY();

        }
        if (grid.spaceIsEmpty(newX, newY)) {

            grid.setNewCoordinates(newX, newY, this);
            setX(newX);
            setY(newY);
            grid.setEmpty(oldX, oldY);

        }

        antDaysAlive++;
        setMovedThisTurn(true);

    }

}
void DoodleBug::move(Grid& grid) {

    if (!getMovedThisTurn()) {
        if (grid.returnCharAtPosition(getX() - 1, getY()) == 'o') {

            grid.setNewCoordinates(getX() - 1, getY(), this);
            grid.setEmpty(getX(), getY());
            setX(getX() - 1);
            setY(getY());
            daysWithoutEating = 0;

        }
        else if (grid.returnCharAtPosition(getX() + 1, getY()) == 'o') {

            grid.setNewCoordinates(getX() + 1, getY(), this);
            grid.setEmpty(getX(), getY());
            setX(getX() + 1);
            setY(getY());
            daysWithoutEating = 0;

        }
        else if (grid.returnCharAtPosition(getX(), getY() - 1) == 'o') {

            grid.setNewCoordinates(getX(), getY() - 1, this);
            grid.setEmpty(getX(), getY());
            setX(getX());
            setY(getY() - 1);
            daysWithoutEating = 0;

        }
        else if (grid.returnCharAtPosition(getX(), getY() + 1) == 'o') {

            grid.setNewCoordinates(getX(), getY() + 1, this);
            grid.setEmpty(getX(), getY());
            setX(getX());
            setY(getY() + 1);
            daysWithoutEating = 0;

        }
        else {
            int direction = rand() % 4 + 1;
            int newX = getX();
            int newY = getY();
            int oldX = getX();
            int oldY = getY();
            daysWithoutEating++;

            if (direction == 1) {

                newX = getX();
                newY = getY() - 1;

            }
            if (direction == 2) {

                newX = getX();
                newY = getY() + 1;

            }
            if (direction == 3) {

                newX = getX() - 1;
                newY = getY();

            }
            if (direction == 4) {

                newX = getX() + 1;
                newY = getY();

            }
            if (grid.spaceIsEmpty(newX, newY)) {

                grid.setNewCoordinates(newX, newY, this);
                setX(newX);
                setY(newY);
                grid.setEmpty(oldX, oldY);

            }
        }
        doodlebugDaysAlive++;
        setMovedThisTurn(true);
    }

}
void Grid::progressWorld() {
    //moves doodlebugs
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {

            if (grid[i][j]->getChar() == 'X')
                grid[i][j]->move(*this);

        }
    }
    //breeds doodlebugs
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {

            if (grid[i][j]->getChar() == 'X')
                grid[i][j]->breed(*this);

        }
    }
    //check if doodlebugs are dead
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {

            if (grid[i][j]->getChar() == 'X')
                grid[i][j]->dies(*this);

        }
    }
    //moves ants
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {

            if (grid[i][j]->getChar() == 'o')
                grid[i][j]->move(*this);

        }
    }
    //breeds ants
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {

            if (grid[i][j]->getChar() == 'o')
                grid[i][j]->breed(*this);

        }
    }
    //resets movement for next turn
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {

            if (grid[i][j]->getChar() == 'o')
                grid[i][j]->setMovedThisTurn(false);

        }
    }
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {

            if (grid[i][j]->getChar() == 'X')
                grid[i][j]->setMovedThisTurn(false);

        }
    }
    timeStepCounter++;
}
void Ant::breed(Grid& grid) {

    if (antDaysAlive >= 3) {

        if (grid.spaceIsEmpty(getX() - 1, getY())) {

            grid.setNewAnt(getX() - 1, getY());
            this->setAntDaysAlive(0);

        }
        else if (grid.spaceIsEmpty(getX() + 1, getY())) {

            grid.setNewAnt(getX() + 1, getY());
            this->setAntDaysAlive(0);

        }
        else if (grid.spaceIsEmpty(getX(), getY() - 1)) {

            grid.setNewAnt(getX(), getY() - 1);
            this->setAntDaysAlive(0);

        }
        else if (grid.spaceIsEmpty(getX(), getY() + 1)) {

            grid.setNewAnt(getX(), getY() + 1);
            this->setAntDaysAlive(0);

        }
    }
}
void DoodleBug::breed(Grid& grid) {

    if (doodlebugDaysAlive == 8) {

        if (grid.spaceIsEmpty(getX() - 1, getY())) {

            grid.setNewDoodleBug(getX() - 1, getY());
            this->setDoodleBugDaysAlive(0);

        }
        else if (grid.spaceIsEmpty(getX() + 1, getY())) {

            grid.setNewDoodleBug(getX() + 1, getY());
            this->setDoodleBugDaysAlive(0);

        }
        else if (grid.spaceIsEmpty(getX(), getY() - 1)) {

            grid.setNewDoodleBug(getX(), getY() - 1);
            this->setDoodleBugDaysAlive(0);

        }
        else if (grid.spaceIsEmpty(getX(), getY() + 1)) {

            grid.setNewDoodleBug(getX(), getY() + 1);
            this->setDoodleBugDaysAlive(0);

        }
    }

}
void DoodleBug::dies(Grid& grid) {

    if (daysWithoutEating == 3) {

        grid.setEmpty(getX(), getY());

    }

}