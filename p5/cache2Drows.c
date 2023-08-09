////////////////////////////////////////////////////////////////////////////////
// Main File:        cache2Drows.c
// This File:        cache2Drows.c
// Other Files:      cache1D.c cache2Dcols.c cache2Dclash.c
// Semester:         CS 354 Summer 2023
// Instructor:       jaso
//
// Author:           Yujin Wang
// Email:            ywang2589@wisc.edu
// CS Login:         yujin
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
//////////////////////////// 80 columns wide ///////////////////////////////////
int arr2D[3000][500];

int main(){
    for (int row = 0; row < 3000; row++){
        for (int col = 0; col < 500; col++){
            arr2D[row][col] = row + col;
        }
    }
}