#include <cstdlib>
#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include <math.h>
using namespace std;


int main(int argc, char const *argv[])
{
   char inputSpamFile[50];
   char inputHamFile[50];
   char inString[100];
   char trainingWord[50];
   char tempCString[100];
   char tempChar;
   int charIndex = 0;
   int parseIdx = 0;
   int copyIdx = 0;
   int hamSize, spamSize;
   int wordFreq;
   string tempString;
   bool hamFlag;

   map <string, int> spamMap;
   map <string, int> hamMap;
   ifstream fin;
   ofstream fout;
   //Parse command line arguments
   for(int i = 1; i < argc; i++)
      {

          if( strcmp( argv[i], "-is" ) == 0 ){
              strcpy(inputSpamFile, argv[i+1] );              
            }
          else if ( strcmp( argv[i], "-ih" ) == 0 ){
              strcpy(inputHamFile, argv[i+1] );
            }
          else if ( strcmp( argv[i], "-s" ) == 0 ){
              strcpy( inString, argv[i+1] );
            }
      }

   //read in ham file
   fin.open( inputHamFile, fstream::in );
   if( !fin ){
      cout << "ham file open failed! ";
      exit(EXIT_FAILURE);
   }
   fin >> hamSize;
   //cout << hamSize;
   //read in ham file  
   while( fin.get( tempChar ) ){
      if( tempChar != ' ' && tempChar != '\n' ){
         tempCString[ charIndex ] = tempChar;
         charIndex++;
      }
      //else if space delimiter, then next object is word frequency
      else if( tempChar == ' ' ){
         tempCString[ charIndex ] = '\0';
         //read in word frequency
         fin >> wordFreq;
         //assign c string to string object
         tempString = tempCString;
         hamMap[tempString] = wordFreq;
         //cout << tempString << ' ' << wordFreq << endl;
         //reset temp c string
         tempCString[0] = '\0';
         charIndex = 0;
      }
   }
   fin.close();

   //read in spam file
   fin.open( inputSpamFile, fstream::in );
   if( !fin ){
      cout << "spam file open failed! ";
      exit(EXIT_FAILURE);
   }
   fin >> spamSize;

   while( fin.get( tempChar ) ){
      if( tempChar != ' ' && tempChar != '\n' ){
         tempCString[ charIndex ] = tempChar;
         charIndex++;
         //strcat(tempCString, tempChar );
      }
      //else if space delimiter, then next object is word frequency
      else if( tempChar == ' ' ){
         tempCString[ charIndex ] = '\0';
         //read in word frequency
         fin >> wordFreq;
         //assign c string to string object
         tempString = tempCString;
         spamMap[tempString] = wordFreq;
         //cout << tempString << ' ' << wordFreq << endl;
         //reset temp c string
         tempCString[0] = '\0';
         charIndex = 0;
      }
   }
   fin.close();
  
   //parse input string
   //loop over whole string
   tempChar = inString[0];   
   while( tempChar != '\0' ){
      //test if alphanumeric
      if( isalnum( tempChar ) || tempChar == '\''){
         //copy into trainingWord
         trainingWord[ copyIdx ] = inString[ parseIdx ];
         charIndex++;
      }
      //else run into delimiter
      else{
         trainingWord[ charIndex ] = '\0';
         //if word is ham, then set flag to true
         if( strcmp(trainingWord, "ham") ){
            hamFlag = true;
         }
         //if word is spam then set hamFlag to false
         else if( strcmp(trainingWord, "spam") ){
            hamFlag = false;
         }
         //otherwise add word into map
         else{
            if( hamFlag && trainingWord[0] != '\0' ){
               tempString = trainingWord;
               hamMap[ tempString ]++;
            }
            else if( !hamFlag && trainingWord[0] != '\0' ){
               tempString = trainingWord;
               spamMap[ tempString ]++;
            }
         }
         charIndex = 0;
         trainingWord[0] = '\0';
      }
      parseIdx++;
      tempChar = inString[ parseIdx ];
   }   
   

   //output ham file
   fout.open( inputHamFile, fstream::out );
   //print out number of ham words
   fout << hamMap.size() << '\n';
   //loop over and print values of map
   for( map<string,int>::iterator it=hamMap.begin(); it!=hamMap.end(); ++it ){
     fout << it->first << ' ' << it->second << '\n';
   }

   fout.close();

   //output spam file
   fout.open( inputSpamFile, fstream::out );
   //print out number of spam words
   fout << spamMap.size() << '\n';
    //loop over and print values of map
    for( map<string,int>::iterator it=spamMap.begin(); it!=spamMap.end(); ++it ){
     fout << it->first << ' ' << it->second << '\n';
   }
   fout.close();

   return 0;
}