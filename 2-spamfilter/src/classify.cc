//This file contains the classifier. Input is .csv file of task, output will give each item a specifier of ham or spam.
//Written by Xiang Li for CS682: Artificial Intelligence
//20181028

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

//declare struct for holding sentence and probabilities
struct classResults{
   char sentence[300];
   char cType[20];

};

int main(int argc, char const *argv[])
{
   char testFile[20];
   char spamFile[20];
   char hamFile[20];
   char outFile[20];
   char tempCString[100];
   char tempSentString[300];
   char junkString[100];
   int charIndex = 0;
   int sentIdx = 0;
   int commaCtr = 0;
   int resultsIdx = 0;
   int hamSize, spamSize;
   int wordFreq = 0;
   
   int freqThreshold = 3;

   double hamProb, spamProb, WSprob, WHprob, SWprob;
   map <int, classResults> testMap;
   string tempString;

   char tempChar;
   map <string, int> spamMap;
   map <string, int> hamMap;
   ifstream fin;
   ofstream fout;

   //Parse command line arguments
   for(int i = 1; i < argc; i++)
      {

          if( strcmp( argv[i], "-i" ) == 0 ){
              strcpy(testFile, argv[i+1] );              
            }
          else if ( strcmp( argv[i], "-is" ) == 0 ){
              strcpy(spamFile, argv[i+1] );
            }
          else if ( strcmp( argv[i], "-ih" ) == 0 ){
              strcpy( hamFile, argv[i+1] );
            }
          else if (strcmp( argv[i], "-o") == 0 ){
              strcpy( outFile, argv[i+1] );
          }
      }
   //read in ham file
   fin.open( hamFile, fstream::in );
   if( !fin ){
      cout << "ham file open failed! ";
      exit(EXIT_FAILURE);
   }
   fin >> hamSize;
   //cout << hamSize;
   //read in pam file  
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
   fin.open( spamFile, fstream::in );
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
   //calculate hamProb and spamProb
   hamProb = hamSize / (hamSize+spamSize);
   spamProb = spamSize / (hamSize+spamSize);
   //calculate initial values of WSprob and WHprob
   WHprob = log10( hamProb );
   WSprob = log10( spamProb );
   //cout << endl << "Size of map: " << spamMap.size();
   //cout << endl << "Size of map: " << spamSize;

   //read in input test file
   fin.open( testFile, fstream::in );
   if( !fin ){
      cout << "Test File open failed! ";
      exit(EXIT_FAILURE);
   }
   //ignore first line
   fin >> junkString;
   //cout << junkString;
   //reinitialize tempCString
   tempCString[0] = '\0';
   //read in test file character by character
   while( fin.get(tempChar) ){
      //copy characters to test map sentence
      testMap[ resultsIdx ].sentence[ sentIdx ] = tempChar;
      //If alphanumeric or apostrophe then add to string
      if( isalnum( tempChar ) || tempChar == '\'' ){
         tempCString[ charIndex ] = tempChar;
         charIndex++;
      }
      //otherwise reached some delimiter
      else{
         //test to see if end of line
         if( tempChar == ',' && fin.peek() == ',' ){
            testMap[ resultsIdx ].sentence[ sentIdx ] = '\0';
            //test to see if P(W|S) > P(W|H), then it is more likely to be spam
            if( WSprob > WHprob ){
               strcpy(testMap[ resultsIdx ].cType, "spam");
            }
            //otherwise, it is ham
            else{
               strcpy(testMap[ resultsIdx ].cType, "ham");
            } 

            //increment index for next sentence
            resultsIdx++;
            //reset probs to base probabilities P(S) and P(H)
            WHprob = log10( hamProb );
            WSprob = log10( spamProb );
            //reset sentence index, -1 because this increases at every character read in
            sentIdx = -1;
            //get next chars, otherwise this will loop 2x since there
            //are 3 commas for delimiter in input file.
            fin.get(tempChar);
            fin.get(tempChar);
         }
         //otherwise not end of line but just a delimeter between words
         else{
            //put terminating character into temp string
            tempString[ charIndex ] == '\0';
            //calculate probability of WS and WH
            tempString = tempCString;
            if( spamMap[ tempString ] > freqThreshold ){
               WSprob+= log10( spamMap[ tempString ] / spamSize );
            }
   
            if( hamMap[ tempString ] > freqThreshold ){
               WHprob+= log10( hamMap[ tempString ] / hamSize );
            }
         }
         //reset character index for next word
         charIndex = 0;
      }  
     //increment sentence index for next character
     sentIdx++;
   }
   fin.close();

   fout.open( outFile, fstream::out );
   //cout << testMap.size();
   for(int i = 0; i < testMap.size(); i++ ){
      cout << testMap[i].sentence << ' ' << testMap[i].cType << endl;
   }
   //Output results file
   for( int i = 0; i < (testMap.size() - 1); i++ ){
      fout << testMap[i].sentence << ' ' << testMap[i].cType;
   }

   /*for( map<int, classResults>::iterator it=testMap.begin(); it!=testMap.end(); ++it ){
     fout << it->first << ' ' << it->second << '\n';
   }*/
   fout.close();
   return 0;
}
