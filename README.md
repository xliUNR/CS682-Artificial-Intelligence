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
  
# project 3

Implement a kalman filter to estimate state of 1D robot that has position x and velocity xdot. Sensor output is position only.

# project 4

Implement Reinforcement learning, specifically Q-learning, using the OpenAI gym environment.
First file cart.py is a solution to the cartpole balancing environment. Program learns how to balance pole on a cart for 200 ticks of time.
Second file car.py is solution to mountain car. Program must learn how to get up a hill by rocking back and forth in a valley.


  
