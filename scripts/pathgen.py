PATHLENGTH = 10
MINDIST = 0.1
VELOCITY = 0.2
MAXRANGE = 10
DEBUG = False
from random import random
from math import pow, sqrt
from sys import exit

class Point():

    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def dist(self, other):
        return sqrt(pow((self.x-other.x), 2)+ pow((self.y-other.y), 2)+ pow((self.z-other.z), 2))

    def vector_towards(self, other):
        dist = self.dist(other)
        return Point((other.x-self.x)/dist, (other.y-self.y)/dist, (other.z-self.z)/dist)

#       using points to represent vectors here because why not


    def __eq__(self, other):
        if type(self) != type(other):
            return NotImplemented
        else:
            return other.__dict__ == self.__dict__ 
    

class Mover():
#a point that moves around.
    def __init__(self):
        self.pos = Point(0, 0, 0)
        self.vel = VELOCITY
        self.range = MAXRANGE
        self.target = Point(0, 0, 0)
        self.maxtargets = PATHLENGTH
        self.currenttarget = 0
        self.terminated = False

    def move(self, vector):
        self.pos.x += vector.x * self.vel
        self.pos.y += vector.y * self.vel
        self.pos.z += vector.z * self.vel
    def dist(self, other):
        return self.pos.dist(other)

    def reset_target(self):
        self.target = Point(0,0,0)

    def randomize_target(self):
        self.target.x = (random()-0.5) * self.range
        self.target.y = (random()-0.5) * self.range
        self.target.z = (random()-0.5) * self.range

    def printinfo(self):
#       comma-separated
        niceprint = ','.join((str(self.pos.x), str(self.pos.y), str(self.pos.y)))
        print(niceprint)

    def step(self):
#       move at VELOCITY towards self.target
#       if at target, set next target and increment current target #
#       if at final target, set target to Point(0,0,0)
#       print current position to STDOUT each step
        self.printinfo()
        if self.pos == self.target or self.dist(self.target) < MINDIST:
            if self.currenttarget > self.maxtargets:
                self.terminated = True
                if DEBUG: print("TERMINATING")
                return

            if self.currenttarget == self.maxtargets:
                self.reset_target()
                if DEBUG: print("RETURNING TO ORIGIN")
                self.currenttarget += 1
            else:
                self.randomize_target() 
                if DEBUG: print("TARGET CHANGE")
                self.currenttarget +=1    
                

#       no need to else here
        if not self.terminated:
            self.move(self.pos.vector_towards(self.target))
        else:
            if DEBUG: print("IT'S OVER")
            exit()

        

goose = Mover()
while not goose.terminated:
    goose.step()
exit()

