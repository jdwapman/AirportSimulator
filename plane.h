//
//  plane.h
//  AirlinePerfect
//
//  Created by Jonathan Wapman on 4/29/15.
//  Copyright (c) 2015 Jonathan Wapman. All rights reserved.
//

#ifndef __AirlinePerfect__plane__
#define __AirlinePerfect__plane__

#include <fstream>
#include "city.h"
#include "citylist.h"
using namespace std;

class Plane
{
  char name[12];
  int passengers;
  int range; //In miles
  int speed; //In miles per hour
  int fuel; // In US gallons
  int price; //In US dollars
  
public:
  
  
  void readPlane(ifstream* planeFile, const int numPlanes) const;
  
  void setName(const char* nam); //Sets the plane's name
  
  void setPassengers(const int passengen); //Sets plane's passengers
  
  void setFuel(const int fue); //Sets the fuel
  
  void setRange(const int rang); //Sets the range
  
  void setPrice(const int pric); //Sets the price
  
  void setSpeed(const int spee); //Sets the speed
  
  const char* getName() const;
  
  int getPassengers() const;
  
  int getRange();
  
  void writePlane(ofstream* planeFile) const; //Writes the plane to bin file
  
  double totalCost(const CityList& cities,
                   const int city1, const int city2) const;
  
  double calcFuelCost(const double cityDistance) const;
  
  const double calcAttendantSalary(const double cityDistance) const;
  
  const double calcPilotSalary(const double cityDistance) const;
  
  double calcMaintenanceCost(double cityDistance) const;
  
  void printPlaneInfo();
  
  bool isPlane();
  
  friend ostream& operator << (ostream& os, const Plane &rhs);
  
}; //Plane

static const double gasPrice = 3.39;


#endif
