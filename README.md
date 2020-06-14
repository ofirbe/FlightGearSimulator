##Flight Gear Simulator

Our goal is to flight the plane by sending commands to the simulator.
How can we do that? by dividing the work into two different parts that are running simultaneously:
1. First of all, the simulator should connect to the server as client, and  send its current values that are describing the flight status.
2. Secondly, the program should connect as a client to the simulator server, and send the instrcution commands in order to flight the plane.

##Privious Preparation

First you'll need to install [flight gear](https://www.flightgear.org/)

Then, in the additional settings you'll need to write these lines:
--telnet=socket,in,10,127.0.0.1,5402,tcp
--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small   

In addition you'll need to have a text file of commands and a xml file to put in the protocol folder.
After you have put the xml file in protocol, you can run the program on the command line with an argument which is the fly.txt.
Then you'll need to press fly on the simulator and after 2 minutes the flight will begin. 

## Running

Use the following command to compile, then run a.out (provide txt file name as argument) :
g++ -std=c++14 main.cpp *.cpp  -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread


##Versions

We used [Github](https://github.com/ofirbe/FlightGearSimulator.git) for version control.


##IDE

Clion - Ide by JetBrains

##Authors

- Michael Ternovsky
- Ofir Ben Ezra
