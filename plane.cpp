#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cmath>
#include "plane.h"
#include "citylist.h"

using namespace std;


//Reads a plane's info from the file
void Plane::readPlane(ifstream* planeFile, const int numPlanes) const
{
  planeFile->read((char*)this, sizeof(Plane)); //Reads the info
  //cout << name << "\n";
} //readPlane()

//Writes new plane to the file
void Plane::writePlane(ofstream* planeFile) const
{
  planeFile->write((char*)this, sizeof(Plane));
} //writePlane()

double Plane::totalCost(const CityList& cities, const int
                        cityDistance, const int totalPassengers) const
{
  double totalCost = 0;

  double fuelCost = 0;
  double attendantSalary = 0;
  double pilotSalary = 0;
  double maintenanceCost = 0;
  int trips = 0;
  trips = ceil((double)totalPassengers / (double)passengers);
  
  if (range < cityDistance)
  {
    return 9999999; //Unusable plane
  } //If range is less than distance, not best plane
  
  if (cityDistance < 100)
  {
    return 9999999;
  } //No one flies if distance is less than 100
  
  fuelCost = calcFuelCost(cityDistance); //Calculates fuel cost
  attendantSalary = calcAttendantSalary(cityDistance);
  pilotSalary = calcPilotSalary(cityDistance);
  maintenanceCost = calcMaintenanceCost(cityDistance);
  totalCost = trips *
      (fuelCost + attendantSalary + pilotSalary + maintenanceCost);
  return ceil(totalCost);
} //totalCost()

double Plane::calcFuelCost(const double cityDistance) const
{
  
  double fuelCost = 0;
  double totalGallons = 0;
  double gallonsPerMile = 0;
  
  gallonsPerMile = (double)fuel / (double)range; //Calculates miles per gallon
  
  totalGallons = (double)cityDistance * (double)gallonsPerMile;
  
  fuelCost = (double)totalGallons * (double)3.39; //$3.39/gallon
  
  return fuelCost;
} //calcFuelCost

//Calculates total cost of paying attendants
const double Plane::calcAttendantSalary(const double cityDistance) const
{
  double salary = 0;
  double numAttendants = 0;
  double flightTime = 0;
  const int groundTime = 2;
  const int costPerHour = 30;
  
  flightTime = ceil(cityDistance / speed); //Time plane is in air
  
  numAttendants = ceil((double)passengers / (double)100);
  
  salary = (double)numAttendants * ((double)costPerHour *
          ((double)flightTime + (double)groundTime));
  
  return salary;
} //calcAttendantSalary


//Calculates the total cost of paying the pilots
const double Plane::calcPilotSalary(const double cityDistance) const
{
  double salary = 0;
  const double numPilots = 2;
  const int groundTime = 2;
  double flightTime = 0;
  const int costPerHour = 100;
  
  flightTime = ceil((double)cityDistance / (double)speed);
  
  salary = (double)numPilots * ((double)costPerHour *
            ((double)flightTime + (double)groundTime));
  
  return salary;
} //calcPilotSalary()

double Plane::calcMaintenanceCost(double cityDistance) const
{
  double maintenanceCost = 0;
  double flightTime = 0;
  
  flightTime = (double)cityDistance / (double)speed;
  
  maintenanceCost = 0.000025 * (double)price * (double)flightTime; //Check this
  
  return maintenanceCost;
} //calcMaintenanceCost()


void Plane::setName(const char* nam)
{
  strcpy(name, nam);
} //setName()

void Plane::setPassengers(const int passengen)
{
  passengers = passengen;
} //setPassengers()

void Plane::setFuel(const int fue)
{
  fuel = fue;
} //setFuel()

void Plane::setPrice(const int pric)
{
  price = pric;
} //setPrice()

void Plane::setRange(const int rang)
{
  range = rang;
} //setRange()

void Plane::setSpeed(const int spee)
{
  speed = spee;
} //setSpeed()

const char* Plane::getName() const
{
  return name;
} //getName()

int Plane::getPassengers() const
{
  return passengers;
} //getPassengers()

int Plane::getRange()
{
  return range;
} //getRange

ostream& operator << (ostream& os, const Plane &rhs)
{
  
  cout << left << setw(12) << rhs.name;
  cout << left << setw(6) << rhs.passengers;
  
  cout << left << rhs.range / 1000 << ","
    << (rhs.range % 1000) / 100 <<
    ((rhs.range % 1000) % 100) / 10
    << setw(2) << ((rhs.range % 1000) % 100) % 10;
  

  cout << left << setw(6) << rhs.speed;
  
  cout << setw(2);
  
  cout << right;
  
  cout  << rhs.fuel / 1000 << ","
  << (rhs.fuel % 1000) / 100 <<
  ((rhs.fuel % 1000) % 100) / 10
   << ((rhs.fuel % 1000) % 100) % 10;
  
  cout << setw(6) << right << setprecision(3) <<
    (double)rhs.range / (double)rhs.fuel;
  
  cout << setw(6);
  cout << right << fixed << setprecision(2) <<
      (double)rhs.fuel * 3.39 / (double)rhs.range;
  
  cout << setw(2) << right << "$";
  cout << setw(5) << right << fixed << setprecision(1)
      << rhs.price / (double)1000000;
  
  cout << "\n";
  return os;
} // << overloaded operator

bool Plane::isPlane()
{
  if (isdigit(name[0]) && isdigit(name[1]))
  {
    return true;
  } //If a valid plane
  else //If not a valid plane
  {
    return false;
  } //If not a valid plane
} //If the entry is a plane