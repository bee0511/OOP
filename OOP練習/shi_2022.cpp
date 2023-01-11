#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void Q1()
{
    ifstream input;
    input.open("grade.txt");
    string stemp;
    char ctemp;
    getline(input, stemp, ';');
    int s_n = stoi(stemp); // number of students
    getline(input, stemp, ';');
    int g_n = stoi(stemp); // number of grades.

    vector<vector<int>> grade_arr;
    vector<int> grade_row;
    int grade;
    vector<string> name_arr;
    for (int i = 0; i < s_n; i++)
    {
        input >> ctemp;
        getline(input, stemp, ';');
        stemp = ctemp + stemp;
        name_arr.push_back(stemp);
        for (int j = 0; j < g_n; j++)
        {
            getline(input, stemp, ';');
            grade = stoi(stemp);
            // cout << "grade: " << grade << endl;
            grade_row.push_back(grade);
        }
        grade_arr.push_back(grade_row);
        grade_row.clear();
    }
    //
    string name;
    float fsum = 0;
    cout << "Please type a name: ";
    cin >> name;
    int name_index = -1;
    for (int i = 0; i < s_n; i++)
    {
        if (name_arr[i] == name)
        {
            name_index = i;
            break;
        }
    }
    if (name_index == -1)
    {
        cout << "No such student." << endl;
        return;
    }
    for (int i = 0; i < g_n; i++)
    {
        cout << grade_arr[name_index][i] << ";";
        fsum += grade_arr[name_index][i];
    }
    cout << endl;
    int isum = fsum /= g_n;
    if ((int)(fsum + 0.5) != (int)isum)
    {
        isum += 1;
    }
    cout << "Avg: " << isum << endl;
}

void Q2()
{
    ifstream input;
    input.open("grade.txt");
    string stemp;
    char ctemp;
    getline(input, stemp, ';');
    int s_n = stoi(stemp); // number of students
    getline(input, stemp, ';');
    int g_n = stoi(stemp); // number of grades.

    vector<vector<int>> grade_arr;
    vector<int> grade_row;
    int grade;
    vector<string> name_arr;
    for (int i = 0; i < s_n; i++)
    {
        input >> ctemp;
        getline(input, stemp, ';');
        stemp = ctemp + stemp;
        name_arr.push_back(stemp);
        for (int j = 0; j < g_n; j++)
        {
            getline(input, stemp, ';');
            grade = stoi(stemp);
            // cout << "grade: " << grade << endl;
            grade_row.push_back(grade);
        }
        grade_arr.push_back(grade_row);
        grade_row.clear();
    }
    //
    ofstream output;
    output.open("FinalGrade.txt");
    vector<int> avg_arr;
    for (int i = 0; i < s_n; i++)
    {
        float fsum = 0;
        for (int j = 0; j < g_n; j++)
        {
            fsum += grade_arr[i][j];
        }
        int isum = fsum /= g_n;
        if ((int)(fsum + 0.5) != (int)isum)
        {
            isum += 1;
        }
        avg_arr.push_back(isum);
    }
    for (int j = 0; j < s_n; j++)
    { // bubble sort
        for (int k = j + 1; k < s_n; k++)
        {
            if (avg_arr[j] < avg_arr[k])
            {
                int temp = avg_arr[j];
                avg_arr[j] = avg_arr[k];
                avg_arr[k] = temp;
                string stemp = name_arr[j];
                name_arr[j] = name_arr[k];
                name_arr[k] = stemp;
            }
        }
    }
    for (int i = 0; i < s_n; i++)
    {
        cout << name_arr[i] << "'s avg: " << avg_arr[i] << " (";
        output << name_arr[i] << "'s avg: " << avg_arr[i] << " (";
        if (avg_arr[i] >= 60)
        {
            cout << "pass)" << endl;
            output << "pass)" << endl;
        }
        else
        {
            cout << "fail)" << endl;
            output << "fail)" << endl;
        }
    }
}

void Q3()
{
    ifstream input;
    input.open("grade.txt");
    string stemp;
    char ctemp;
    getline(input, stemp, ';');
    int s_n = stoi(stemp); // number of students
    getline(input, stemp, ';');
    int g_n = stoi(stemp); // number of grades.

    vector<vector<int>> grade_arr;
    vector<int> grade_row;
    int grade;
    vector<string> name_arr;
    for (int i = 0; i < s_n; i++)
    {
        input >> ctemp;
        getline(input, stemp, ';');
        stemp = ctemp + stemp;
        name_arr.push_back(stemp);
        for (int j = 0; j < g_n; j++)
        {
            getline(input, stemp, ';');
            grade = stoi(stemp);
            // cout << "grade: " << grade << endl;
            grade_row.push_back(grade);
        }
        grade_arr.push_back(grade_row);
        grade_row.clear();
    }
    int op = 0;
    while (op != 3)
    {
        cout << "1. Show a student's grades from the highest to the lowest and the associated avg." << endl
             << "2. Show the avg. for each student from the highest to the lowest" << endl
             << "3. Exit and output a final report " << endl
             << "Choose an option (1-3):";
        cin >> op;
        switch (op)
        {
        case 1:
        {
            string name;
            float fsum = 0;
            cout << "Please type a name: ";
            cin >> name;
            int name_index = -1;
            for (int i = 0; i < s_n; i++)
            {
                if (name_arr[i] == name)
                {
                    name_index = i;
                    break;
                }
            }
            if (name_index == -1)
            {
                cout << "No such student." << endl;
                break;
            }
            for (int i = 0; i < g_n; i++)
            {
                cout << grade_arr[name_index][i] << ";";
                fsum += grade_arr[name_index][i];
            }
            cout << endl;
            int isum = fsum /= g_n;
            if ((int)(fsum + 0.5) != (int)isum)
            {
                isum += 1;
            }
            cout << "Avg: " << isum << endl;
            break;
        }
        case 2:
        {
            ofstream output;
            output.open("FinalGrade.txt");
            vector<int> avg_arr;
            for (int i = 0; i < s_n; i++)
            {
                float fsum = 0;
                for (int j = 0; j < g_n; j++)
                {
                    fsum += grade_arr[i][j];
                }
                int isum = fsum /= g_n;
                if ((int)(fsum + 0.5) != (int)isum)
                {
                    isum += 1;
                }
                avg_arr.push_back(isum);
            }
            for (int j = 0; j < s_n; j++)
            { // bubble sort
                for (int k = j + 1; k < s_n; k++)
                {
                    if (avg_arr[j] < avg_arr[k])
                    {
                        int temp = avg_arr[j];
                        avg_arr[j] = avg_arr[k];
                        avg_arr[k] = temp;
                        string stemp = name_arr[j];
                        name_arr[j] = name_arr[k];
                        name_arr[k] = stemp;
                    }
                }
            }
            for (int i = 0; i < s_n; i++)
            {
                cout << name_arr[i] << "'s avg: " << avg_arr[i] << " (";
                output << name_arr[i] << "'s avg: " << avg_arr[i] << " (";
                if (avg_arr[i] >= 60)
                {
                    cout << "pass)" << endl;
                    output << "pass)" << endl;
                }
                else
                {
                    cout << "fail)" << endl;
                    output << "fail)" << endl;
                }
            }
            break;
        }
        }
    }
    ofstream output;
    output.open("FinalGrade.txt");
    vector<int> avg_arr;
    for (int i = 0; i < s_n; i++)
    {
        float fsum = 0;
        for (int j = 0; j < g_n; j++)
        {
            fsum += grade_arr[i][j];
        }
        int isum = fsum /= g_n;
        if ((int)(fsum + 0.5) != (int)isum)
        {
            isum += 1;
        }
        avg_arr.push_back(isum);
    }
    for (int j = 0; j < s_n; j++)
    { // bubble sort
        for (int k = j + 1; k < s_n; k++)
        {
            if (avg_arr[j] < avg_arr[k])
            {
                int temp = avg_arr[j];
                avg_arr[j] = avg_arr[k];
                avg_arr[k] = temp;
                string stemp = name_arr[j];
                name_arr[j] = name_arr[k];
                name_arr[k] = stemp;
            }
        }
    }
    for (int i = 0; i < s_n; i++)
    {
        output << name_arr[i] << "'s avg: " << avg_arr[i] << " (";
        if (avg_arr[i] >= 60)
        {
            output << "pass)" << endl;
        }
        else
        {
            output << "fail)" << endl;
        }
    }
}

int main()
{
    // Q1();
    // Q2();
    Q3();
}