# cs482-fall2018
Project Code For cs482/682 Fall 2018 @ UNR

# project 1

Create a tic-tac-toe move-maker program. I've given you some skeleton file I/O code that you can use and the spec for some functions that you have to fill in. Make those functions work, and you should get an 'A'

## to compile

```
mkdir build && cd build
cmake ..
make
```

# project 2

Create spam filter using niave Bayes classifier to give sms either ham or spam classification
Project includes a training program that takes a .csv file of texts and parses it to train the Baye's classifier. Output are two files (one for spam and one for ham) with frequencies of words.
The second file is the classifier that takes in a file as input and outputs a file that gives a classification of ham or spam for each sentence.
The third file, addtotraining, takes in command line argument of a sentence to be added to the output files from the training program. 
Arguments:
training -i <training file> -os <output spam probability file> -oh <output ham probability file>
classify  -i <dataset to be classified> -is <spam probability file> -ih <ham probability file>
addtotraining -is <input spam probability file> -ih <input ham probability file> -s "<string>"
  
