#!/usr/bin/python

import argparse
import logging
import sys

import numpy as np

import gym
#import gym.scoreboard.scoring
from gym import wrappers, logger

#Global variables
OUTOFBOUNDSTATE = -1; 
X_MAX = 0.6
X_MIN = -1.2
X_RANGE = 1.8; 

XDOT_MAX = 0.7
XDOT_MIN = -0.7
XDOT_RANGE = 1.4 

################################################
# CS482: this is the function that changes the
# continuous values of the state of the cart-
# pole into a single integer state value, you'll
# have to adjust this for the mountain car task
################################################

# Function to descritize state, could potientially be parallelized with 
# mapReduce technique
def discretize_state( x, xdot, xRes, xdotRes ):
    # Return -1 for out of bounds state
    if X_MIN > x > X_MAX:
        return OUTOFBOUNDSTATE

    if XDOT_MIN > xdot > XDOT_MAX:
        return OUTOFBOUNDSTATE

    #Calculates x and y coordinates of state.  
    s_x = discretize_state_helper(x, xRes, X_MAX, X_MIN, X_RANGE)
    s_y = discretize_state_helper(xdot, xdotRes, XDOT_MAX, XDOT_MIN, XDOT_RANGE)
    #return flattened value which corresponds to unique index of state
    return s_x * xdotRes + s_y

# Helper function that bins state variables and returns state in 1D
def discretize_state_helper( val, res, maxi, mini, rng ):
    for box in range(res):
        if val < ( rng*(1+box)/res + mini ): 
            return box

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=None)

    ############################################
    # CS482: This is the line you'll have to
    # change to switch to the mountain car task
    ############################################
    parser.add_argument('env_id', nargs='?', default='MountainCar-v0', help='Select the environment to run')
    args = parser.parse_args()

    logger = logging.getLogger()
    formatter = logging.Formatter('[%(asctime)s] %(message)s')
    handler = logging.StreamHandler(sys.stderr)
    handler.setFormatter(formatter)
    logger.addHandler(handler)

    # You can set the level to logging.DEBUG or logging.WARN if you
    # want to change the amount of output.
    logger.setLevel(logging.INFO)

    env = gym.make(args.env_id)
    outdir = '/tmp/' + 'qagent' + '-results'
    env = wrappers.Monitor(env, outdir, write_upon_reset=True, force=True)

    env.seed(0)

    ############################################
    # CS482: This initial Q-table size should 
    # change to fit the number of actions (columns)
    # and the number of observations (rows)
    ############################################


    Q = np.zeros([41, env.action_space.n])

    ############################################
    # CS482: Here are some of the RL parameters
    # you can adjust to change the learning rate
    # (alpha) and the discount factor (gamma)
    ############################################

    alpha = 0.7  
    gamma = 0.97
    
    #Resolution variables for state space   
    xres = 10
    xdotres = 4    

    n_episodes = 50001
    for episode in range(n_episodes):
        tick = 0
        reward = 0
        done = False
        state = env.reset()
        s = discretize_state(state[0], state[1], xres, xdotres )
        while done != True:
            tick += 1
            action = 0
            ri = -999
            for q in range(env.action_space.n):
                if Q[s][q] > ri:
                    action = q
                    ri = Q[s][q]
            state, reward, done, info = env.step(action)
            #print( reward, done)
            sprime = discretize_state(state[0], state[1], xres, xdotres )
            predicted_value = np.max(Q[sprime])
            if sprime < 0:
                predicted_value = 0
                reward = -5
            
            Q[s,action] += alpha*(reward + gamma*predicted_value - Q[s,action])
            #print(Q[s,action], ri, sprime, Q[s][action])
            s = sprime

        if episode % 1000 == 0: 
            alpha *= .99 #decay rate for alpha, each 1000
            print reward
        ############################################
        # CS482: When switching to the mountain car
        # task, you will have to change this to
        # reflect the success/failure of the mountain
        # car task
        ############################################
       
        if state[0] >= 0.5:
            print "success"
        else:
            if episode % 1000 ==0:
                print "fail ", state[0], Q[s,action]