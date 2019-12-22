//
// Created by michael on 16/12/2019.
//

#include "Parser.h"
#include <iostream>
#include <queue>

// definition of the global variable
map<string, Var *> varMap;
map<string, Command *> commandsMap;
map<string, double> flightDataMap;
queue <string> connectControlQueue;

Parser::Parser() {
  commandsMap["connectControlClient"] = new ConnectControlClient();
  commandsMap["openDataServer"] = new OpenDataServer();
  commandsMap["Sleep"] = new SleepCommand();
  commandsMap["Print"] = new PrintCommand();
  commandsMap["while"] = new WhileCommand();
  commandsMap["if"] = new IfCommand();
  commandsMap["var"] = new VarCommand();
}

void Parser::parse(vector<string> vct) {
  int index = 0;
  initializeFlightDataMap();
  while (index < vct.size()) {
    // it is a command from the map
    if (commandsMap.find(vct[index]) != commandsMap.end()) {
      Command *command = commandsMap.find(vct[index])->second;
      index += command->execute(vct, index);
    } else {
      // the rest of the cases: x = 4
      Command *command = commandsMap.find("var")->second;
      index += command->execute(vct, index);
    }
  }
}

//initialize the map that contain all the flight data that exist at the xml file. (36 values initialize to 0)
//we will get the value of all the data from the connection to the flight server.
void Parser::initializeFlightDataMap(){
  flightDataMap["/instrumentation/airspeed-indicator/indicated-speed-kt"] = 0; //airspeed-indicator line 1
  flightDataMap["/sim/time/warp"] = 0; //time_warp line 2
  flightDataMap["/controls/switches/magnetos"] = 0; //switches_magnetos line 3
  flightDataMap["//instrumentation/heading-indicator/offset-deg"] = 0; //heading-indicator line 4                ///////there is 2 "/" at the xml. maybe a problem.
  flightDataMap["/instrumentation/altimeter/indicated-altitude-ft"] = 0; //altimeter_indicated line 5
  flightDataMap["/instrumentation/altimeter/pressure-alt-ft"] = 0; //altimeter_pressure line 6
  flightDataMap["/instrumentation/attitude-indicator/indicated-pitch-deg"] = 0; //attitude-indicator-pitch line 7
  flightDataMap["/instrumentation/attitude-indicator/indicated-roll-deg"] = 0; //attitude-indicator-roll line 8
  flightDataMap["/instrumentation/attitude-indicator/internal-pitch-deg"] = 0; //attitude-indicator_internal-pitch lin 9
  flightDataMap["/instrumentation/attitude-indicator/internal-roll-deg"] = 0; //attitude-indicator_internal-roll line 10
  flightDataMap["/instrumentation/encoder/indicated-altitude-ft"] = 0; //encoder_indicated-altitude line 11
  flightDataMap["/instrumentation/encoder/pressure-alt-ft"] = 0; //encoder_pressure line 12
  flightDataMap["/instrumentation/gps/indicated-altitude-ft"] = 0; //gps_indicated-altitude line 13
  flightDataMap["/instrumentation/gps/indicated-ground-speed-kt"] = 0; //gps_indicated-ground-speed line 14
  flightDataMap["/instrumentation/gps/indicated-vertical-speed"] = 0; //gps_indicated-vertical-speed line 15
  flightDataMap["/instrumentation/heading-indicator/indicated-heading-deg"] = 0; //indicated-heading line 16
  flightDataMap["/instrumentation/magnetic-compass/indicated-heading-deg"] = 0; //magnetic-compass-heading line 17
  flightDataMap["/instrumentation/slip-skid-ball/indicated-slip-skid"] = 0; //slip-skid-ball_indicated line 18
  flightDataMap["/instrumentation/turn-indicator/indicated-turn-rate"] = 0; //turn-indicator line 19
  flightDataMap["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"] = 0; //vertical-speed-indicator line 20
  flightDataMap["/controls/flight/aileron"] = 0; //flight_aileron line 21
  flightDataMap["/controls/flight/elevator"] = 0; //flight_elevator line 22
  flightDataMap["/controls/flight/rudder"] = 0; //flight_rudder line 23
  flightDataMap["/controls/flight/flaps"] = 0; //flight_flaps line 24
  flightDataMap["/controls/engines/engine/throttle"] = 0; //engine_throttle line 25
  flightDataMap["/controls/engines/current-engine/throttle"] = 0; //current-engine_throttle line 26
  flightDataMap["/controls/switches/master-avionics"] = 0; //switches_master-avionics line 27
  flightDataMap["/controls/switches/starter"] = 0; //switches_starter line 28
  flightDataMap["/engines/active-engine/auto-start"] = 0; //active-engine_auto-start line 29
  flightDataMap["/controls/flight/speedbrake"] = 0; //flight_speedbrake line 30
  flightDataMap["/sim/model/c172p/brake-parking"] = 0; //c172p_brake-parking line 31
  flightDataMap["/controls/engines/engine/primer"] = 0; //engine_primer line 32
  flightDataMap["/controls/engines/current-engine/mixture"] = 0; //current-engine_mixture line 33
  flightDataMap["/controls/switches/master-bat"] = 0; //switches_master-bat line 34
  flightDataMap["/controls/switches/master-alt"] = 0; //switches_master-alt line 35
  flightDataMap["/engines/engine/rpm"] = 0; //engine_rpm line 36
}