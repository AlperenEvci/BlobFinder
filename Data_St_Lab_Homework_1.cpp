
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include <iomanip>
// These are the all required libraries for this homework.

using namespace std;

// This is the visualization function.Just used for visualization.

void Cursor_Movement(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Before the solving the main problem We defined class here , so that our steps are decreasing importantly which are must to do.
class Blob {
private:
    float sum_X;
    float sum_Y;
    float Num_Points;

    int Blob_Number;
    int row;
    int col;

public:
    vector<vector<char>> My_Array;
    Blob() :sum_X(0), sum_Y(0), Num_Points(0), Blob_Number(0), row(0), col(0) {}

    // This function is used for the reading our input data from the file. 

    bool Read_Data_File() {
        string File_Name;
        cout << "Please enter the name of the file: ";
        cin >> File_Name;

        ifstream Text_File(File_Name);

        if (!Text_File) {
            cout << "File could not be opened: " << File_Name << endl;
            return false;
        }
        //First of all this function take the column data before taking cells data (each X renamed here as cells).
        Text_File >> row >> col;

        // After the taking size values there must be an array for the write the data into.

        My_Array.resize(row, vector<char>(col));
        for (int r = 0; r < row; ++r) {
            Text_File.ignore();
            for (int c = 0; c < col; ++c) {
                char value;
                Text_File.get(value);
                My_Array[r][c] = value;
            }
        }

        Text_File.close();

        return true;
    }

    // We wrote this function so that our visual output was a little different and we could easily fit the array where we wanted.
    void Final_Print() {


        // We print the borders on the right and left side
        for (int i = 0; i < row; i++) {
            int bar = 219;

            Cursor_Movement(16, 3 + i);
            cout << "|";

            Cursor_Movement(17 + col, 3 + i);
            cout << "|";

            Cursor_Movement(14, 3 + i);
            cout << i;

            Cursor_Movement(19 + col, 3 + i);
            cout << i;

        }

        // We print the borders above and below
        for (int i = 0; i <= col; i++) {
            int bar = 220;
            Cursor_Movement(16 + i, 2);
            cout << "-";

            Cursor_Movement(16 + i, 3 + row);
            cout << "-";
        }

        for (int i = 0; i < col; i++) {
            Cursor_Movement(17 + i, 1);
            cout << i % 10;

            Cursor_Movement(17 + i, 4 + row);
            cout << i % 10;
        }


        // We move the array to the desired location with the help of the Cursor_Movement() function.
        for (int r = 0; r < row; ++r) {

            for (int c = 0; c < col; ++c) {

                Cursor_Movement(17 + c, 3 + r);
                cout << My_Array[r][c];
            }

        }
        cout << endl << endl << endl << endl;

        // Since this section will remain constant in any case, we did a manual printing process.
        cout << "+--------+---------------+-------------+--------------+" << endl;
        cout << "|BLOB NO |  NoOfPixels   | CoM Row     | CoM Column   |" << endl;
        cout << "+--------+---------------+-------------+--------------+" << endl;
    }

    // We assume that this is a DFS(Deep First Search) algorithm. And this is the most important function that which is the include main algorithm which is called DFS algorithm.

    void Blob_Search(int r, int c) {
        
        if (r < 0)
            return;
        if (r >= row)
            return;
        if (c < 0)
            return;
        if (c >= col)
            return;
        if (My_Array[r][c] != 'x')
            return;

        My_Array[r][c] = ' ';

        sum_X += r;
        sum_Y += c;
        Num_Points++;

        //These Are The Main Recursive Steps. This steps are recuired for the find each blobs by using connected cells. There are the main calculations for the search below.
        Blob_Search(r - 1, c);
        Blob_Search(r + 1, c);
        Blob_Search(r, c - 1);
        Blob_Search(r, c + 1);
    }

    void Each_Blob_Search() {


        for (int r = 0; r < row; ++r) {

            for (int c = 0; c < col; ++c) {

                if (My_Array[r][c] == 'x') {

                    sum_X = 0;
                    sum_Y = 0;
                    Num_Points = 0;

                    Blob_Search(r, c);

                    if (Num_Points > 0) {
                        Blob_Number++;
                        // This section is a little bit tricky. We used the columns as puzzles blocks.

                        cout << "|       " << fixed << setprecision(2) << Blob_Number << "|          " << Num_Points << "|         " << float(sum_X / Num_Points) << "|          " << float(sum_Y / Num_Points) << "|" << endl;;
                        cout << "+--------+---------------+-------------+--------------+" << endl;
                    }
                }
            }
        }
    }
};

int main() {
    Blob blob;
    if (!blob.Read_Data_File()) {
        return 1;
    }
    blob.Final_Print();
    blob.Each_Blob_Search();

    return 0;
}