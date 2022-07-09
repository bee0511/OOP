//********************************************
// Student Name			:
// Student ID			:
// Student Email Address:
//********************************************
//
// Prof. Sai-Keung Wong
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/04/25
//
// Add your own functions if necessary
//
#ifndef __MY_2048_SYSTEM_H_
#define __MY_2048_SYSTEM_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
#include "base_class.h"
#include "graph_basics.h"

using std::vector;

#define MAX_2048_NX 10
#define MAX_2048_NZ 10

class MY_2048 : public BASE_SYSTEM {
protected:
    void draw_GridCell( int ix, int iz ) const;
    void draw_GridCells( ) const;
    void draw_Board( ) const;
    void draw_Event( ) const;

    void reset( );
    void generateNumber( );
    void moveDown( );
    void moveUp( );
    void moveLeft( );
    void moveRight( );
    //
    void generateNumbers_All_2to4( );
    void generateNumbers_All_2to8( );
    void generateNumbers_All( );

    void performAction( unsigned char key );

    //
    // Implement your own stuff
    //
public:
    MY_2048( );
    MY_2048( int nx, int nz );
    void setDimension(int nx, int nz);
    void draw( ) const;
    void askForInput( );
    void handleKeyPressedEvent( unsigned char key );
    void handleSpecialKeyPressedEvent( unsigned char key );
    void setPosition( int x, int z );
    void setFocus( bool flg );
    //
    void update( );

    bool isAutoPlay() const;
    bool isBoardFull() const;
    //
    void copyPrevious( const BASE_SYSTEM *m );
    void copyRightBoard(const BASE_SYSTEM* m);
    //
    int getBestAction(MY_2048* board, int d);
    int performAction_Recur(int action, MY_2048* board, int d);
    int evaluateScore(MY_2048* board);
    //
    int DetermineNextMove(MY_2048* board);
    int calculateScore(MY_2048* board, int move);
    MY_2048* simulateMove(MY_2048* board, int move);
    int generateScore(MY_2048* board, int currentDepth, int depthLimit);
    int calculateMoveScore(MY_2048* newBoard2, int currentDepth, int depthLimit);
    int calculateFinalScore(MY_2048* board);
    //
    int calculateEmptyCells(MY_2048* board);
    int BoardMaxNumber(MY_2048* board);

    //
    void CopyCurrentBoard(MY_2048* m);
    void PrintBoard();
    //
    int calculateEmptyCellsInRow(MY_2048* board, int row);
    int calculateEmptyCellsInColumn(MY_2048* board, int column);
    int calculateMergesInRow(MY_2048* board, int row);
    int calculateMergesInColumn(MY_2048* board, int column);
    int calculateSumInRow(MY_2048* board, int row);
    int calculateSumInColumn(MY_2048* board, int column);

protected:
    ///////////////////////////////////////////
    bool mFlgFocus;
    int mPositionX, mPositionZ;
    unsigned char mEvent;
    ///////////////////////////////////////////
    int mNX, mNZ;
    int mBoard[MAX_2048_NZ][MAX_2048_NX];
    //
    int mPreviousBoard[MAX_2048_NZ][MAX_2048_NX];
    //
    bool flg_AutoPlay;
    bool flg_FullBoard;
    //
    //
    // Implement your own stuff
    //
};

#endif