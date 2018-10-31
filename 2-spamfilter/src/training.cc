//This file contains training for classifier
//Written by Xiang Li for CS682: Artificial Intelligence
//20181028
//
#include <cstdlib>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <string.h>
using namespace std;


int main(int argc, char const *argv[])
{
   //declare variables
   char inFile[20];
   char outSpam[20];
   char outHam[20];
   char tempString[100];
   char tempString2[100]; 
   //string inFile, outSpam, outHam;
   //string tempString, tempString2;
   ifstream fin;
   ofstream fout;
   map <char*, int> spamMap;
   map <char*, int> hamMap;
   
   //Parse command line arguments
   for(int i = 1; i < argc; i++)
      {

          if( strcmp( argv[i], "-i" ) == 0 ){
              strcpy(inFile, argv[i+1] );              
            }
          else if ( strcmp( argv[i], "-os" ) == 0 ){
              strcpy(outSpam, argv[i+1] );
            }
          else if ( strcmp( argv[i], "-oh" ) == 0 ){
              strcpy( outHam, argv[i+1] );
            }
      }

   //Open file and check if worked
   fin.open( inFile, fstream::in );
   if( !fin ){
       cout << "File open failed!";
       exit( EXIT_FAILURE );
     }
   fin >> tempString;
   //cout << tempString;
   char* tempString3;
   size_t len;
   //getdelim(&tempString, &len, ',', fin );
   //getline(fin, tempString);
   //fin >> tempString;
   //tempString3 = strtok( tempString, ",\"");
   //cout << tempString3;
   //fin.get(tempString,200, ',');
   //fin.get(tempString2, 200,',');
   //fin >> tempString;
   //getdelim(&tempString, 
   //cout << tempString << endl;
   //cout << tempString3;
   //fin >> tempString;
   //cout << tempString2 << endl;
   for( int i = 0; i < 5; i++){
       fin >> tempString;
       cout << "tempString: " << tempString << endl;
       tempString3 = strtok( tempString, ",.\"");
       cout << "tempString3: " << tempString3 << endl;
       tempString3 = strtok( NULL, ",.\"");

       cout << tempString3 << endl;
    }

   //Read in line by line and parse each word. 
   //loop over all words in input file
   //read in lines until next line
   //loop over all words in sms 
   //Compare first word, check if word == spam or ham and put into array
   /*if( tempWord == "ham")
      {
        ctr = hamWords[ tempWord ] 
   */
   //update counter

   //print output file
   //One for ham one for spam number of words.

   return 0;
}
