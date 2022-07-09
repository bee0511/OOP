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
#include "mySystem_2048.h"
#include <iostream>

using namespace std;

static unsigned char specialKeys[] = {
    GLUT_KEY_UP,
    GLUT_KEY_DOWN,
    GLUT_KEY_LEFT,
    GLUT_KEY_RIGHT
};

int numSpecialKeys = sizeof(specialKeys)/sizeof(unsigned char);

MY_2048::MY_2048( )
{
    mNX = 4;
    mNZ = 4;
    reset( );

    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    flg_AutoPlay = false;
    flg_FullBoard = false;
}

MY_2048::MY_2048( int nx, int nz )
{
    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    // Implement your own stuff
    //
    mNX = 4;
    mNZ = 4;
    reset();

    flg_AutoPlay = false;
    flg_FullBoard = false;
}

void MY_2048::setDimension(int nx, int nz)
{
    mFlgFocus = true;
    
    //
    // Implement your own stuff
    //

    mNX = nx;
    mNZ = nz;
    reset();
}


void MY_2048::setFocus( bool flg )
{
    mFlgFocus = flg;
}

void MY_2048::setPosition( int x, int z )
{
    mPositionX = x;
    mPositionZ = z;
}

//
// Copy the m's previous board 
// to the object's mBoard.
//
void MY_2048::copyPrevious( const BASE_SYSTEM *m )
{
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            mBoard[j][i] = ((MY_2048*)m)->mPreviousBoard[j][i];
        }
    }
}

void MY_2048::copyRightBoard(const BASE_SYSTEM* m)
{
    for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            ((MY_2048*)m) ->mPreviousBoard[j][i] = mBoard[j][i];
        }
    }
}

//
//reset the game board
//
void MY_2048::reset( )
{
    mEvent = 0;
    ///////////////////////////////////////
    //
    // Implement your own stuff
    //
    for (int j = 0; j < mNZ; j++) {
        for (int i = 0; i < mNX; i++) {
            mBoard[j][i] = 0;
            mPreviousBoard[j][i] = 0;
        }
    }
    flg_AutoPlay = false;
    flg_FullBoard = false;
}

//
// show messages and ask for input (if any)
//
void MY_2048::askForInput( )
{
    //
    // Implement your own stuff
    //
    cout << "MY_2048" << endl;
    cout << "Key usage:" << endl;
    cout << "1: generate randomly the numbers 2 and 4 for all the cells" << endl;
    cout << "2: generate randomly the numbers 2, 4 and 8 for all the cells" << endl;
    cout << "3: generate randomly the numbers for all the cells" << endl;
    cout << "r: clear all the cells" << endl;
    cout << " " << endl;
    cout << "UP, DOWN, LEFT, RIGHT: move the numbers to the respective side" << endl;
    cout << "a or A: To automatically play for one step." << endl;
    cout << "spacebar: toggle the autoplay mode. " << endl;
}

//
// randomly generate a new number
//
void MY_2048::generateNumber( )
{
    //
    // Implement your own stuff
    //
    bool gen_flag = false;
    int random_Z, random_X;
    int** tried_board = new int*[mNX];
    for (int i = 0; i < mNZ; i++) {
        tried_board[i] = new int[mNZ];
    }
    for (int i = 0; i < mNX; i++) {
        for (int j = 0; j < mNZ; j++) {
            tried_board[j][i] = 0;
        }
    }
    while (!gen_flag) {
        int count = 0;
        random_Z = rand() % mNZ;
        random_X = rand() % mNX;
        if (mBoard[random_Z][random_X] == 0) {
            int value = 1 + rand() % 2;
            int number = 1;
            number = number << value;
            mBoard[random_Z][random_X] = number;
            gen_flag = true;
        }
        else {
            tried_board[random_Z][random_X] = 1;
        }
        for (int i = 0; i < mNX; i++) {
            for (int j = 0; j < mNZ; j++) {
                if (tried_board[j][i] == 0) break;
                else count++;
                if (count == mNX * mNZ) {
                    cout << "Error: the Board is full" << endl;
                    gen_flag = true;
                    flg_AutoPlay = false;
                    flg_FullBoard = true;
                }
            }
        }
    }
    for (int i = 0; i < mNZ; i++) {
        delete [] tried_board[i];
    }
    delete[] tried_board;
}


void MY_2048::moveDown( )
{
    //
    // Implement your own stuff
    //    
    for (int i = 0; i < mNX; i++) {

        for (int j = 0; j < mNZ; j++) {
            for (int k = j + 1; k < mNZ; k++) {//merge
                if (mBoard[k][i] != 0 && mBoard[k][i] != mBoard[j][i]) {
                    break;
                }
                if (mBoard[j][i] == mBoard[k][i] && mBoard[j][i] != 0) {
                    mBoard[j][i] *= 2;
                    mBoard[k][i] = 0;
                    //cout << "break" << endl;
                    break;
                }
            }
            for (int k = j; k > 0; k--) {//move down
                if (mBoard[k - 1][i] == 0) {
                    mBoard[k - 1][i] = mBoard[k][i];
                    mBoard[k][i] = 0;
                }
            }
        }
    }
}

void MY_2048::moveUp( )
{
    //
    // Implement your own stuff
    //
    for (int i = 0; i < mNX; i++) {
        for (int j = mNZ; j >= 0; j--) {
            for (int k = j - 1; k >= 0; k--) {//merge
                if (mBoard[k][i] != 0 && mBoard[k][i] != mBoard[j][i]) {
                    break;
                }
                if (mBoard[j][i] == mBoard[k][i] && mBoard[j][i] != 0) {
                    mBoard[j][i] = 0;
                    mBoard[k][i] *= 2;
                    //cout << "break" << endl;
                    break;
                }
            }
            //cout << "Column" << i << " after merge : " << endl;
            //PrintBoard();
            for (int k = 0; k < mNZ; k++) {//move up
                if (mBoard[k + 1][i] == 0 && k + 1 != mNZ) {
                    mBoard[k + 1][i] = mBoard[k][i];
                    mBoard[k][i] = 0;
                }
            }
            //cout << "Column" << i << " after move up: " << endl;
            //PrintBoard();
        }
    }
}

void MY_2048::moveLeft( )
{
    //
    // Implement your own stuff
    //
    for (int j = 0; j < mNZ; j++) {

        for (int i = 0; i < mNX; i++) {
            for (int k = i + 1; k < mNX; k++) {//merge
                if (mBoard[j][k] != 0 && mBoard[j][k] != mBoard[j][i]) {
                    break;
                }
                if (mBoard[j][i] == mBoard[j][k] && mBoard[j][i] != 0) {
                    mBoard[j][i] *= 2;
                    mBoard[j][k] = 0;
                    //cout << "break" << endl;
                    break;
                }
            }
            for (int k = i; k > 0; k--) {//move left
                if (mBoard[j][k - 1] == 0) {
                    mBoard[j][k - 1] = mBoard[j][k];
                    mBoard[j][k] = 0;
                }
            }
        }
    }
}

void MY_2048::moveRight( )
{
    //
    // Implement your own stuff
    //
    for (int j = 0; j < mNZ; j++) {
        for (int i = mNX; i >= 0; i--) {
            for (int k = i - 1; k >= 0; k--) {//merge
                if (mBoard[j][k] != 0 && mBoard[j][k] != mBoard[j][i]) {
                    break;
                }
                if (mBoard[j][i] == mBoard[j][k] && mBoard[j][i] != 0) {
                    mBoard[j][i] = 0;
                    mBoard[j][k] *= 2;
                    //cout << "break" << endl;
                    break;
                }
            }
            for (int k = 0; k < mNX; k++) {//move right
                if (mBoard[j][k + 1] == 0 && k + 1 != mNX) {
                    mBoard[j][k + 1] = mBoard[j][k];
                    mBoard[j][k] = 0;
                }
            }
        }
    }
}

void MY_2048::generateNumbers_All_2to4( )
{
    //
    // Implement your own stuff
    //
    for (int j = 0; j < mNZ; j++) {
        for (int i = 0; i < mNX; i++) {
            int value = 1 + rand() % 2;
            int number = 1;
            number = number << value;
            mBoard[j][i] = number;
        }
    }
}

void MY_2048::generateNumbers_All_2to8( )
{
    //
    // Implement your own stuff
    //
    for (int j = 0; j < mNZ; j++) {
        for (int i = 0; i < mNX; i++) {
            int value = 1 + rand() % 3;
            int number = 1;
            number = number << value;
            mBoard[j][i] = number;
        }
    }
}

void MY_2048::generateNumbers_All( )
{
    //
    // Implement your own stuff
    //
    for (int j = 0; j < mNZ; j++) {
        for (int i = 0; i < mNX; i++) {
            int value = 1 + rand() % 11;
            int number = 1;
            number = number << value;
            mBoard[j][i] = number;
        }
    }
}

void MY_2048::handleKeyPressedEvent( unsigned char key )
{
    switch( key ) {
    case 'r':
    case 'R':
        reset( );
        break;
    case '1':
        generateNumbers_All_2to4( );
        copyRightBoard(this);
        break;
    case '2':
        generateNumbers_All_2to8( );
        copyRightBoard(this);
        break;
    case '3':
        generateNumbers_All( );
        copyRightBoard(this);
        break;

    case 'a':
    case 'A':
        //flg_AutoPlay
        //for one step
        flg_AutoPlay = true;
        update();
        flg_AutoPlay = false;
        break;
    case ' ':
        // toggle to auto-play
        flg_AutoPlay = !flg_AutoPlay;
        update();
        break;
    }
}

void MY_2048::performAction( unsigned char key ) {
bool flgDone = false;
    switch( key ) {
    case GLUT_KEY_UP:
        flgDone = true;
        copyRightBoard(this);
        moveUp( );
        mEvent = GLUT_KEY_UP;
        break;
    case GLUT_KEY_DOWN:
        flgDone = true;
        copyRightBoard(this);
        moveDown( );
        mEvent = GLUT_KEY_DOWN;

        break;
    case GLUT_KEY_LEFT:
        flgDone = true;
        copyRightBoard(this);
        moveLeft( );
        mEvent = GLUT_KEY_LEFT;

        break;
    case GLUT_KEY_RIGHT:
        flgDone = true;
        copyRightBoard(this);
        moveRight( );
        mEvent = GLUT_KEY_RIGHT;
        break;

    }

    if ( flgDone ) {
        generateNumber( );
    }
}

void MY_2048::handleSpecialKeyPressedEvent( unsigned char key )
{
    //
    // It takes a long time to show a message!
    //
    cout << "MY_2048::handleSpecialKeyPressedEvent:" << key << endl;
    performAction( key );
}

bool MY_2048::isAutoPlay() const
{
    return flg_AutoPlay;
}

bool MY_2048::isBoardFull() const {
    return flg_FullBoard;
}

//
// The update( ) function is called every frame.
//
// Design an algorithm to automatically perform
// one step.
//
void MY_2048::update( )
{
    //
    // It takes a long time to show a message!
    //
    cout << "MY_2048::update( )" << endl;
    cout << "MY_2048::flg_AutoPlay:\t" << flg_AutoPlay << endl;

    if (!flg_AutoPlay) return;

    //
    // Implement your own stuff
    //
    int bestmove = 0;
    //bestmove = DetermineNextMove(this);
    bestmove = getBestAction(this, 7);
    switch (bestmove) {
    case 0:
        performAction(GLUT_KEY_UP);
        mEvent = GLUT_KEY_UP;
        break;
    case 1:
        performAction(GLUT_KEY_DOWN);
        mEvent = GLUT_KEY_DOWN;
        break;
    case 2:
        performAction(GLUT_KEY_LEFT);
        mEvent = GLUT_KEY_LEFT;
        break;
    case 3:
        performAction(GLUT_KEY_RIGHT);
        mEvent = GLUT_KEY_RIGHT;
        break;
    }

}


int MY_2048::getBestAction(MY_2048* board, int d) {
    int bestScore = -1;
    int bestAction = 0;
    if (d <= 0) return bestAction;
    for (int action = 0; action < 4; action++) {
        MY_2048* tempBoard = simulateMove(board, action);
        int score = performAction_Recur(action, tempBoard, d - 1);
        if (score > bestScore) {
            bestScore = score;
            bestAction = action;
        }
    }
    return bestAction;
}

int MY_2048::performAction_Recur(int action, MY_2048* board, int d) {
    int score = -1;
    int bestScore = -1;
    if (d == 0) {
        score = evaluateScore(board);
        return score;
    }
    for (int action = 0; action < 4; action++) {
        MY_2048* tempBoard = simulateMove(board, action);
        score = performAction_Recur(action, tempBoard, d - 1);
        if (score > bestScore) {
            bestScore = score;
        }
    }
    return score;
}

int MY_2048::evaluateScore(MY_2048* board) {
    int score = 0;
    score = calculateEmptyCells(board);
    return score;
}

MY_2048* MY_2048::simulateMove(MY_2048* board, int move) {
    MY_2048* newBoard = board;
    switch (move) {
    case 0:
        newBoard->moveDown();
        break;
    case 1:
        newBoard->moveUp();
        break;
    case 2:
        newBoard->moveLeft();
        break;
    case 3:
        newBoard->moveRight();
        break;
    }
    return newBoard;
}
//
int MY_2048::DetermineNextMove(MY_2048* board) {
    int bestmove = 0;
    int bestscore = 0;
    for (int i = 0; i < 4; i++) {
        int score = calculateScore(board, i);
        if (score > bestscore) {
            bestscore = score;
            bestmove = i;
        }
    }
    return bestmove;
}

int MY_2048::calculateScore(MY_2048* board, int move) {
    MY_2048* newBoard = simulateMove(board, move);
    int count = 0;
    for (int j = 0; j < mNZ; j++) {
        for (int i = 0; i < mNX; i++) {
            if (board->mBoard[j][i] == mBoard[j][i]) {
                count++;
                if (count == mNZ * mNX) return 0;//the same board
            }
        }
    }
    return generateScore(newBoard, 0, 7);
}

int MY_2048::generateScore(MY_2048* board, int currentDepth, int depthLimit) {
    if (currentDepth == depthLimit) {
        return calculateFinalScore(board);
    }
    int totalScore = 0;
    for (int j = 0; j < mNZ; j++) {
        for (int i = 0; i < mNX; i++) {
            if (board->mBoard[j][i] == 0) {
                MY_2048* newBoard2 = board;
                newBoard2->mBoard[j][i] = 2;
                int moveScore2 = calculateMoveScore(newBoard2, currentDepth, depthLimit);
                totalScore += 0.5 * moveScore2; // suppose 2 has 50% happen
                MY_2048* newBoard4 = board;
                newBoard4->mBoard[j][i] = 2;
                int moveScore4 = calculateMoveScore(newBoard4, currentDepth, depthLimit);
                totalScore += 0.5 * moveScore4; // suppose 4 has 50% happen
            }
        }
    }
    return totalScore;
}

int MY_2048::calculateMoveScore(MY_2048* board, int currentDepth, int depthLimit) {
    int bestScore = 0;
    for (int i = 0; i < 4; i++) {
        MY_2048* newBoard = simulateMove(board, i);
        if (newBoard != board) {
            int score = generateScore(newBoard, currentDepth + 1, depthLimit);
            if (score > bestScore) bestScore = score;
        }
    }
    return bestScore;
}

int MY_2048::calculateFinalScore(MY_2048* board) {
    int score = 0;
    int FIXED_SCORE = 0, EMPTY_SCORE = 1, MERGES_SCORE = 0, SUM_SCORE = 1, MAX_SCORE = 0;
    for (int i = 0; i < mNZ; i++) {
        score += FIXED_SCORE;
        score += EMPTY_SCORE * calculateEmptyCellsInRow(board, i);
        score += MERGES_SCORE * calculateMergesInRow(board, i);
        score -= SUM_SCORE * calculateSumInRow(board, i);
    }
    for (int i = 0; i < mNX; i++) {
        score += FIXED_SCORE;
        score += EMPTY_SCORE * calculateEmptyCellsInColumn(board, i);
        score += MERGES_SCORE * calculateMergesInColumn(board, i);
        score -= SUM_SCORE * calculateSumInColumn(board, i);
    }
    score += MAX_SCORE * BoardMaxNumber(board);
    return score;
}

int MY_2048::calculateEmptyCellsInRow(MY_2048* board, int row) {
    int number = 0;
    for (int i = 0; i < mNX; i++) {
        if (board->mBoard[row][i] == 0) number++;
    }
    return number;
}

int MY_2048::calculateEmptyCellsInColumn(MY_2048* board, int column) {
    int number = 0;
    for (int i = 0; i < mNZ; i++) {
        if (board->mBoard[i][column] == 0) number++;
    }
    return number;
}

int MY_2048::calculateMergesInRow(MY_2048* board, int row) {
    int number = 0;
    for (int i = 0; i < mNX; i++) {
        for (int k = i + 1; k < mNX; k++) {//merge
            if (board->mBoard[row][k] != 0 && board->mBoard[row][k] != board->mBoard[row][i]) {
                break;
            }
            if (board->mBoard[row][i] == board->mBoard[row][k] && board->mBoard[row][i] != 0) {
                number++;
                break;
            }
        }
    }
    return number;
}

int MY_2048::calculateMergesInColumn(MY_2048* board, int column) {
    int number = 0;
    for (int j = 0; j < mNZ; j++) {
        for (int k = j + 1; k < mNZ; k++) {//merge
            if (board->mBoard[k][column] != 0 && board->mBoard[k][column] != board->mBoard[j][column]) {
                break;
            }
            if (board->mBoard[j][column] == board->mBoard[k][column] && board->mBoard[j][column] != 0) {
                number++;
                break;
            }
        }
        return number;
    }
}

int MY_2048::calculateSumInRow(MY_2048* board, int row) {
    int sum = 0;
    for (int i = 0; i < mNX; i++) {
        sum += board->mBoard[row][i];
    }
    return sum;
}

int MY_2048::calculateSumInColumn(MY_2048* board, int column) {
    int sum = 0;
    for (int i = 0; i < mNZ; i++) {
        sum += board->mBoard[i][column];
    }
    return sum;
}

int MY_2048::calculateEmptyCells(MY_2048* board) {
    int sum = 0;
    for (int j = 0; j < mNZ; j++) {
        for (int i = 0; i < mNX; i++) {
            if (board->mBoard[j][i] == 0) sum++;
        }
    }
    return sum;
}

int MY_2048::BoardMaxNumber(MY_2048* board) {
    int max = 0;
    for (int j = 0; j < mNZ; j++) {
        for (int i = 0; i < mNX; i++) {
            if (max < board->mBoard[j][i]) max = board->mBoard[j][i];
        }
    }
    return max;
}

void MY_2048::CopyCurrentBoard(MY_2048* m) {
    for (int j = 0; j < mNZ; j++) {
        for (int i = 0; i < mNX; i++) {
            m->mBoard[j][i] = mBoard[j][i];
        }
    }
}

void MY_2048::PrintBoard() {
    cout << "Current Board: " << endl;
    for (int j = 0; j < mNZ; j++) {
        for (int i = 0; i < mNX; i++) {
            cout << mBoard[j][i] << " ";
        }
        cout << endl;
    }
}