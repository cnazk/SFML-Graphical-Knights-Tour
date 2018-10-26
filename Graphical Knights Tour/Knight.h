//
//  Knight.h
//  Graphical Knights Tour
//
//  Created by Sina Zaker on 8/4/1397 AP.
//  Copyright © 1397 AP Sina Zaker. All rights reserved.
//



//
// Created by Sina Zaker on 10/15/2018 AD.
//

#include <iostream>

#ifndef Knight_h
#define Knight_h

#define TOP_LEFT "╔"
#define TOP "═"
#define TOP_CROSS "╦"
#define TOP_RIGHT "╗"
#define RIGHT_CROSS "╣"
#define RIGHT "║"
#define BOTTOM_RIGHT "╝"
#define LEFT_CROSS "╠"
#define BOTTOM_CROSS "╩"
#define BOTTOM_LEFT "╚"
#define CROSS "╬"
#define KNIGHT "∆∆"

#endif /* Knight_h */

using namespace std;

class Term;

class BoardCell;

class Board;

enum State {
    NotVisited,
    HasVisited,
    AlreadyIn,
};

class Term {
public:
    int x, y;
    
    Term(int x, int y) : x(x), y(y) {}
    
    Term() {}
    
    Term operator+(const Term &rhs) const {
        return Term(rhs.x + x, rhs.y + y);
    }
};

class BoardCell {
private:
    int visitOrder = 0;
    
    void InitializeOrder() {
        order = 0;
        for (int i = 0; i < 8; ++i) {
            if (term.x + AvailableMoves[i].x < 8 && term.x + AvailableMoves[i].x >= 0
                && term.y + AvailableMoves[i].y < 8 && term.y + AvailableMoves[i].y >= 0)
                order++;
        }
    }
    
public:
    
    const static Term AvailableMoves[];
    
    Term term;
    
    Board *_board;
    
    int order;
    
    State state;
    
    BoardCell(Term t, Board* b) {
        _board = b;
        term = t;
        state = State::NotVisited;
        InitializeOrder();
    }
    
    string GetOrder() {
        if (state == State::AlreadyIn)
            return string(KNIGHT);
        if (visitOrder == 0)
            return "  ";
        if (visitOrder < 10)
            return " " + to_string(visitOrder);
        return to_string(visitOrder);
        
    }
    
    int GetDegree();
    
    void MovedIn(int n) {
        state = State::AlreadyIn;
        visitOrder = n;
    }
    
    void MovedOut() {
        state = State::HasVisited;
    }
    
};

class Board {
private:
    BoardCell *cells[8][8];
    
    Term _knightPosition;
    
    int _order = 0;
    
    void PrintTopRow() {
        cout << TOP_LEFT;
        for (int i = 0; i < 7; ++i) {
            cout << TOP << TOP << TOP_CROSS;
        }
        cout << TOP << TOP << TOP_RIGHT << endl;
    }
    
    void PrintMiddleRow(int row, bool withData) {
        for (int i = 0; i < 8; ++i) {
            cout << RIGHT;
            if (withData)
                cout << cells[row][i]->GetOrder();
            else
                cout << "  ";
        }
        cout << RIGHT << endl;
    }
    
    void PrintCross() {
        cout << LEFT_CROSS;
        for (int i = 0; i < 7; ++i) {
            cout << TOP << TOP << CROSS;
        }
        cout << TOP << TOP << RIGHT_CROSS << endl;
    }
    
    void PrintBottomRow() {
        cout << BOTTOM_LEFT;
        for (int i = 0; i < 7; ++i) {
            cout << TOP << TOP << BOTTOM_CROSS;
        }
        cout << TOP << TOP << BOTTOM_RIGHT << endl;
    }
    
    void InitializeCells() {
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
                cells[i][j] = new BoardCell(Term(i, j), this);
    }
    
public:
    
    bool HasGameStarted = false;
    
    Board(Term t) {
        _knightPosition = t;
        InitializeCells();
        cells[_knightPosition.x][_knightPosition.y]->MovedIn(++_order);
        HasGameStarted = true;
    }
    
    Board(){}
    
    void PlaceKnight(Term t) {
        _knightPosition = t;
        InitializeCells();
        cells[_knightPosition.x][_knightPosition.y]->MovedIn(++_order);
        HasGameStarted = true;
    }
    
    BoardCell *Get(int i, int j) {
        if (i > 7 || i < 0
            || j > 7 || j < 0)
            return nullptr;
        return cells[i][j];
    }
    
    bool HasMetAllCells() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (cells[i][j]->state == NotVisited)
                    return 0;
            }
        }
        return 1;
    }
    
    void MoveToLeastOrder() {
        BoardCell * min = NULL;
        for (int i = 0; i < 8; ++i) {
            Term t = BoardCell::AvailableMoves[i] + _knightPosition;
            if (t.x > 7 || t.x < 0
                || t.y > 7 || t.y < 0)
                continue;
            if (Get(t)->state != State::NotVisited)
                continue;
            if (min == NULL || min->GetDegree() > Get(t)->GetDegree())
                min = Get(t);
        }
        if (min == NULL)
            return;
        cells[_knightPosition.x][_knightPosition.y]->MovedOut();
        _knightPosition = min->term;
        cells[_knightPosition.x][_knightPosition.y]->MovedIn(++_order);
    }
    
    BoardCell *Get(Term term) {
        return Get(term.x, term.y);
    }
    
    void PrintBoard() {
        PrintTopRow();
        for (int i = 0; i < 7; ++i) {
            PrintMiddleRow(i, true);
            PrintCross();
        }
        PrintMiddleRow(7, true);
        PrintBottomRow();
    }
};

int BoardCell::GetDegree() {
    int ret = 0;
    for (int i = 0; i < 8; ++i) {
        Term t = AvailableMoves[i];
        BoardCell * c = _board->Get(t + term);
        if (c != nullptr && c->state == NotVisited)
            ret++;
    }
    return ret;
    
}

const Term BoardCell::AvailableMoves[] = {
    Term(-2,-1),
    Term(-2,1),
    Term(2,-1),
    Term(2,1),
    Term(-1,-2),
    Term(-1,2),
    Term(1,-2),
    Term(1,2),
};
