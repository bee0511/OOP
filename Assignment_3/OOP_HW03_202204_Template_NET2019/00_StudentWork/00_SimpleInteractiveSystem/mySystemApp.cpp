//
// Prof. Sai-Keung Wong
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/04/25
//
#include "mySystemApp.h"

using namespace std;

void MY_SYSTEM_APP::showStudentInfo_2022( ) const
{
	cout << "*******************************" << endl;
	cout << "Date:2022/06/09\t" << endl;
	cout << "Student ID:\t110550164" << endl;
	cout << "Student Name:\t´å«Ø®p" << endl;
	cout << "Student Email:\tbee000092.cs10@nycu.edu.tw" << endl;
	cout << "*******************************" << endl;
}

void MY_SYSTEM_APP::showMenu( ) const
{
    /*cout << "Welcome to our mini-galaxy!" << endl;
    cout << "Menu----------------------" << endl;
    cout << "Key usage:" << endl;
    cout << "F1: Monte Carlo Simulation" << endl;
    cout << "F2: Galaxy" << endl;
    cout << "F3: Painter" << endl;
    cout << "F4: Visualization of Bubble Sort" << endl;
    cout << "F5: Simple File Reader" << endl;
    cout << endl;
    cout << "r: reset" << endl;

    cout << "--------------------------" << endl;*/
    cout << "--------------------------" << endl;
    cout << "Key usages:" << endl
        << "F1: perform Graph System" << endl
        << "F2 : perform My_2048 with dimension 4x4." << endl
        << "Press the spacebar to toggle the autoplay mode." << endl
        << "Press ¡¥a¡¦ or ¡¥A¡¦ to perform an action automatically for one step." << endl
        << "F3 : perform My_2048 with dimension 8x8" << endl
        << "F4 : perform Image System" << endl
        << "F5 : show your student information." << endl
        << "i, I : ask for input(to see other key usages in the current system)" << endl
        << "s, S : show the student information" << endl;
    cout << "--------------------------" << endl;

}

MY_SYSTEM_APP::MY_SYSTEM_APP( )
{
	mSystemType = SYSTEM_TYPE_GALAXY_SYSTEM;
//    mColorPalette = new COLOR_PALETTE;
    //
    mCurSystem = 0;
}

void MY_SYSTEM_APP::initApp( )
{
	mFlgShow_Grid = false;
    showMenu( );
    //
    mGraphSystem = new GRAPH_SYSTEM;
    mMy2048 = new MY_2048;
    //
//    mTrafficSystem = new TRAFFIC_SYSTEM;

    //
    mCurSystem = mMy2048;
    //mCurSystem = mTrafficSystem;

    mImageSystem = new IMAGE_SYSTEM;

    mCurSystem = mImageSystem;

    ////////////////////////////////////////////
    ((MY_2048*)mMy2048)->setPosition( 30.0, 0);

    mPrev_2048 = new MY_2048;
    mPrev_2048->setPosition( 0.0, 0);
    mPrev_2048->setFocus( false );
    //
    specialFunc(GLUT_KEY_F1, 0, 0);
}

void MY_SYSTEM_APP::update( )
{
    if ( mCurSystem == mMy2048 ) {
        if ( mCurSystem->isAutoPlay() ) {
            mCurSystem->update( );
        }
         return;
    }
    mCurSystem->update( );
    return;
    switch( mSystemType ) {
		case SYSTEM_TYPE_MONTE_CARLO_SIMULATION:
//			mMonteCarloSystem.update( );
			break;
		case SYSTEM_TYPE_GALAXY_SYSTEM:
//			mGalaxySystem.update( );
			break;
		case SYSTEM_TYPE_SIMPLE_PAINTER:
//			mSimplePainter.update( );
			break;
		case SYSTEM_TYPE_SORTING_VISUALIZATION:
//			mSortingVisualization.update( );
			break;
        case SYSTEM_TYPE_SIMPLE_FILE_EDITOR:
//            mSimpleFileEditor.update( );
            break;
	}
}




