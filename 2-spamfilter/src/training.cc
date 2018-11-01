//This file contains training for classifier
//Written by Xiang Li for CS682: Artificial Intelligence
//20181028
//
#include <cstdlib>
#include <stdio.h>
#include <ctype.h>
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
   char junkString[100]; 
   char tempChar;
   int charIndex = 0;
   bool hamFlag;
   ifstream fin;
   ofstream fout;
   map <string, int> spamMap;
   map <string, int> hamMap;
   string mapStr;
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

   //Ignore first line
   fin >> junkString;
    
   //initialize empty string
   tempString[0] = '\0';
   //loop and read character until end of file is reached
   while( fin.get(tempChar) ){
     //cout << " Input Char: " << tempChar << endl ;
     //test to see if alphanumberic or an apostrophe  
     if( isalnum( tempChar ) || tempChar == '\''){
       //copy into temporary string if so and advance iterator  
       tempString[ charIndex ] = tempChar;
       charIndex++;
     } 
     //otherwise it reached a delimeter between words
     else{
       //put terminating character into tempString
       tempString[ charIndex ] = '\0'; 
        //cout << "Word is: " << tempString << ' ';
       //if word stored is ham, then set flag to add to ham map  
       if( strcmp( tempString, "ham" ) == 0 ){
          //cout << "Word is ham!" << endl; 
          hamFlag = true;
       }
       //if word is spam, then set flag to false to add to spam map
       else if( strcmp( tempString, "spam" ) == 0 ){
          //cout << "Word is spam!" << endl;
          hamFlag = false;
       }
       //not ham or spam so must be a word to add to maps
       //need to check for empty string.
       else{
          
          if( hamFlag && tempString[0] != '\0' ){
              //add word to ham map
            //cout << "word added: " << tempString << endl;
            mapStr = tempString;
            hamMap[ mapStr ]++;
          }
          else if( !hamFlag && tempString[0] != '\0' ){
              //add word to spam map
            //cout << "word added: " << tempString << endl;
            mapStr = tempString;
            spamMap[ mapStr ]++;
          }
       }   

       //reset charIndex and tempString
       charIndex = 0;
       tempString[0] = '\0';    
     }
   }
   //close file stream
   fin.close();
   cout << endl << "Size of ham map: " << hamMap.size();
   cout << endl << "Size of spam map: " << spamMap.size();
   
   //output ham file
   fout.open( outHam, fstream::out );
   //print out number of ham words
   fout << hamMap.size() << '\n';
   //loop over and print values of map
   for( map<string,int>::iterator it=hamMap.begin(); it!=hamMap.end(); ++it ){
     fout << it->first << ' ' << it->second << '\n';
   }

   fout.close();

   //output spam file
   fout.open( outSpam, fstream::out );
   //print out number of spam words
   fout << spamMap.size() << '\n';
    //loop over and print values of map
    for( map<string,int>::iterator it=spamMap.begin(); it!=spamMap.end(); ++it ){
     fout << it->first << ' ' << it->second << '\n';
   }
   fout.close();

   return 0;
}
