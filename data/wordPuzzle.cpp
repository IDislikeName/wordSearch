#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
using namespace std;

// Rather than create a dynamic array - create a static array of 500 by 500 
// and assume that the grid will be less than that size
#define MAXROWS 500
#define MAXCOLS 500
char grid[MAXROWS][MAXCOLS];

/** Read in a grid file into a global grid[][] array.  It uses C++
 * file streams, and thus requires the the <fstream> #include header.
 *
 * @return true or false, depending on whether the file was
 *         successfully opened.
 * @param filename The file name to read in -- it's assumed to be in
 *                 the file format described in the lab document.
 * @param rows The number of rows as specified in the input file;
 *             as this is a reference, it is set by the function.
 * @param cols The number of columnss as specified in the input file;
 *             as this is a reference, it is set by the function.
 */
bool readInGrid(string filename, int &rows, int &cols)
{
    // a C++ string to hold the line of data that is read in
    string line;
    // set up the file stream to read in the file (takes in a C-style
    // char* string, not a C++ string object)
    ifstream file(filename.c_str());
    // upon an error, return false
    if (!file.is_open())
        return false;
    // the first line is the number of rows: read it in
    file >> rows;
    cout << "There are " << rows << " rows." << endl;
    getline(file, line); // eats up the return at the end of the line
    // the second line is the number of cols: read it in and parse it
    file >> cols;
    cout << "There are " << cols << " cols." << endl;
    getline(file, line); // eats up the return at the end of the line
    // the third and last line is the data: read it in
    getline(file, line);
    // close the file
    file.close();
    // convert the string read in to the 2-D grid format into the
    // grid[][] array.  In the process, we'll print the grid to the
    // screen as well.
    int pos = 0; // the current position in the input data
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            grid[r][c] = line[pos++];
            cout << grid[r][c];
        }
        cout << endl;
    }
    // return success!
    return true;
}

/** @return A char* containing the letters in the provided direction
 *         (NOTE: it is returned in a static char array).
 * @param startRow The starting (row,col) position to find the word.
 * @param startCol The starting (row,col) position to find the word.
 * @param dir The direction to move: 0 is north (upwards), 1 is
 *            northeast, and it rotates around clockwise until it
 *            reaches 7 for northwest.
 * @param len The desired length of the string to return (assuming
 *            the edge of the grid is not reached--if the edge of the
 *            grid is reached, it will return as many characters as
 *            possible up to the edge of the grid, so the returned
 *            string may not have the same length as this parameter
 *            indicates).
 * @param numRows The number of rows in the global char grid[][]
 *                array.
 * @param numCols The number of columns in the global char grid[][]
 *                array.
 */
char* getWordInGrid (int startRow, int startCol, int dir, int len,
                     int numRows, int numCols) {
    // the static-ness of this variable prevents it from being
    // re-declared upon each function invocataion.  It also prevents it
    // from being deallocated between invocations.  It's not
    // great programming practice, but it's an efficient means to return
    // the value.
    static char output[256];
    // make sure the length is not greater than the array size.
    if ( len >= 255 )
        len = 255;
    // the position in the output array, the current row, and the
    // current column
    int pos = 0, r = startRow, c = startCol;
    // iterate once for each character in the output
    for ( int i = 0; i < len; i++ ) {
        // if the current row or column is out of bounds, then break
        if ( (c >= numCols) || (r >= numRows) || (r < 0) || (c < 0) )
            break;
        // set the next character in the output array to the next letter
        // in the grid
        output[pos++] = grid[r][c];
        // move in the direction specified by the parameter
        switch (dir) { // assumes grid[0][0] is in the upper-left
            case 0:
                r--;
                break; // north
            case 1:
                r--;
                c++;
                break; // north-east
            case 2:
                c++;
                break; // east
            case 3:
                r++;
                c++;
                break; // south-east
            case 4:
                r++;
                break; // south
            case 5:
                r++;
                c--;
                break; // south-west
            case 6:
                c--;
                break; // west
            case 7:
                r--;
                c--;
                break; // north-west
        }
    }
    // set the next character to zero (end-of-string)
    output[pos] = 0;
    // return the string (a C-style char* string, not a C++ string
    // object)
    return output;
}


int main(int argc, char *argv[])
{
    // cout << "You have entered " << argc << " arguments."
    //      << "\n";

    // first argument is the name of the executable
    // second is the name of the dictionary
    // third is the name of the grid
    // for (int i = 0; i < argc; ++i)
    //     cout << argv[i] << "\n";

    int n_rows, n_cols;
    if (readInGrid((string) argv[2], n_rows, n_cols)) {
        cout << "Grid finished reading." << endl;
    }
    else {
        cout << "ERROR: Grid file not found." << endl;
        exit(1);
    }

    string dict = argv[1];
    unordered_set <string> set;
    string line;
    ifstream d(dict);
    while (getline(d, line))
    {
        if(line.length()>=3)
            set.insert(line);
    }
    d.close();
    int numFound;
    for(int i=0;i<n_rows;i++){
        for(int j=0;j<n_cols;j++){
            for(int k=0;k<8;k++){
                for(int l=3;l<23;l++){
                    string word = getWordInGrid(i,j,k,l,n_rows,n_cols);
                    if(l>word.length()) break;
                    if(set.count(word)){
                        string output;
                        numFound++;
                        if(k==0){
                            output = "N";
                        }
                        else if(k==1){
                            output = "NE";
                        }
                            
                        else if(k==2){
                            output = "E";
                        }   
                        else if(k==3){
                            output = "SE";
                        }    
                        else if(k==4){
                            output = "S";
                        }     
                        else if(k==5){
                            output = "SW";
                        }
                        else if(k==6){
                            output = "W";
                        }
                        else if(k==7){
                            output = "NW";
                        }
                        cout<< output << "(" << i << ", " << j << "): " << word <<endl;
                    }
                }
            }
        }
    }
    cout<<numFound<<" words found."<<endl;

    return 0;
}