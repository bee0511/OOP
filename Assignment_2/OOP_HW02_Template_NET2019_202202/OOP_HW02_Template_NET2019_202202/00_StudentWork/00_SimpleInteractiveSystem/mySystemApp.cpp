//
// Instructor: Sai-Keung WONG
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/03/17
//
#include "mySystemApp.h"

using namespace std;

#define STUDENT_INFO "Name:´å«Ø®p   ID:110550164"

void MY_SYSTEM_APP::showStudentInfo_2022( ) const
{
	cout << "*******************************" << endl;
    cout << "Date:2022/04/28" << endl;
	cout << "Student ID:\t110550164" << endl;
	cout << "Student Name:\t´å«Ø®p" << endl;
	cout << "Student Email:\tbee000092.cs10@nycu.edu.tw" << endl;
	cout << "*******************************" << endl;
    cout << "Spring 2022." << endl;
    cout << "Instructor: Sai-Keung Wong" << endl;
    cout << "*******************************" << endl;
}

const char* MY_SYSTEM_APP::getStudentInfo() const {
    return STUDENT_INFO;
}

void MY_SYSTEM_APP::showMenu( ) const
{
    cout << "Welcome to our mini-galaxy!" << endl;
    cout << "Menu----------------------" << endl;
    cout << "Key usage:" << endl;
    cout << "F1: Monte Carlo Simulation" << endl;
    cout << "F2: Galaxy" << endl;
    cout << "F3: Painter" << endl;
    cout << "F4: Simple File Reader" << endl;
    cout << "F5: Visualization of Bubble Sort" << endl;
    cout << endl;
    cout << "s, S: student information" << endl;

    cout << "--------------------------" << endl;

}

MY_SYSTEM_APP::MY_SYSTEM_APP( )
{
    string title = STUDENT_INFO;
    glutSetWindowTitle(title.data( ));

	//mSystemType = SYSTEM_TYPE_GALAXY_SYSTEM;
    mSystemType = SYSTEM_TYPE_MONTE_CARLO_SIMULATION;
    mColorPalette = new COLOR_PALETTE;
    mCamera->setZoom(-67);
}

void MY_SYSTEM_APP::initApp( )
{
	mFlgShow_Grid = false;
    showMenu( );
}

void MY_SYSTEM_APP::update( )
{
    switch( mSystemType ) {
		case SYSTEM_TYPE_MONTE_CARLO_SIMULATION:
			mMonteCarloSystem.update( );
            updateMonteCarloTitle();
			break;
		case SYSTEM_TYPE_GALAXY_SYSTEM:
			mGalaxySystem.update( );
            updateGalaxySystemTitle();
			break;
		case SYSTEM_TYPE_SIMPLE_PAINTER:
			mSimplePainter.update( );
            updateSimplePainterTitle();
			break;
		case SYSTEM_TYPE_SORTING_VISUALIZATION:
			mSortingVisualization.update( );
            updateSortingVisualizationTitle();
			break;
        case SYSTEM_TYPE_SIMPLE_FILE_EDITOR:
            mSimpleFileEditor.update( );
            updateSimpleFileEditorTitle();
            break;
	}
}




