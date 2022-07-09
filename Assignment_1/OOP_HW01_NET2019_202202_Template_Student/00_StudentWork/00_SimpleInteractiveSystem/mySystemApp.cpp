//
// Instructor: Sai-Keung Wong
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/03/24
//
#include "mySystemApp.h"

using namespace std;

#define STUDENT_INFO "Name:´å«Ø®p   ID:110550164"

void MY_SYSTEM_APP::showMyStudentInfo( ) const
{
	cout << "*******************************" << endl;
    cout << "Date:2022/03/24" << endl;
	cout << "Student ID:\t110550164" << endl;
	cout << "Student Name:\t´å«Ø®p" << endl;
	cout << "Student Email:\tbee000092.cs10@nycu.edu.tw" << endl;
	cout << "*******************************" << endl;
}

MY_SYSTEM_APP::MY_SYSTEM_APP( )
{
	mSystemType = SYSTEM_TYPE_MONTE_CARLO_CIRCLE;
    //string title = STUDENT_INFO;
    //glutSetWindowTitle(title.data( ));
	updateMonteCarloTitle();
}

const char* MY_SYSTEM_APP::getStudentInfo() const {
	return STUDENT_INFO;
}

void MY_SYSTEM_APP::initApp( )
{
	mFlgShow_Grid = true;
}

void MY_SYSTEM_APP::update( )
{

}
// CODE: 2022/03/24. Do not delete this line.



