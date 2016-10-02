#include <cstdlib>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include "city.h"

using namespace std;


//This function initializes an individual city with NULL and 0 values
City::City()
{
  //cout << "Making new city\n";
  strcpy(airport, "***");
  name = NULL; //Sets the name pointer to NULL
  state = NULL; //Sets the state pointer to NULL
  
  latitude = 0; //Sets the latitude to 0
  longitude = 0; //Sets the longitude to 0
  population = 0; //Sets the population to 0
  
  return;
} //initialize()

char* City::getName()
{
  return name;
} //getName()

void City::printList()
{
  cout << name << "\n";
} //printList()

char* City::getState()
{
  return state;
} //getState

void City::readAirport(char* line, char* stat)
{
  char * pch; //Char pointer
  
  state = new char[strlen(stat) + 1];
  strcpy(state, stat);
  
  if (!strncmp(line, "[", 1)) //If the line contains airport info
  {
    pch = strtok (line, "[]");
    
    while (pch != NULL) //This loop stores the values
    {
      
      strcpy(airport, pch); //Stores the airport in the city strucy
      
      pch = strtok (NULL, " "); //Moves to the latitude value
      //Converts the latitude to a double and stores it
      latitude = atof(pch);
      
      pch = strtok (NULL, " "); //Moves to the longitude value
      //Converts the longitute to a double and stores it
      longitude = atof(pch);
      pch = strtok (NULL, ","); //Goes to the city name
      
      //Allocates memory for the city name.
      name = new char[strlen(pch) + 1];
      strcpy(name, pch); //Copies the string
      
      removeFrontSpace(name);
      
      pch = strtok (NULL, " ");
      pch = strtok (NULL, " "); //Goes to the next line of the file
    } //While the pointer character is NULL
  } //Is the line has airport info
} //readAirport()

//This function removes the extra space at the beginning of each name
void City::removeFrontSpace(char* nam)
{
  int i = 0; //Counter variable to loop through string
  
  for (i = 0; i < (int)strlen(nam) - 1; ++i)
  {
    nam[i] = nam[i + 1];
  }//Loops through each individual character in the string
  
  nam[i] = '\0'; //Sets the last character to a null character
  
  nam[i + 1] = '\0'; //Sets the last character to a null character
 
return;
} //removeFrontSpace()

bool City::hasAirport()
{
  if (strcmp(airport, "***") == 0)
  {
    return false;
  } //If there is no airport
  else //If there is no airport
  {
    return true;
  } //If there is an airport
  
} //hasAirport

void City::calcDistance(const City* city2, int* d) const
{
  const int R = 3963;
  
  *d = acos(sin(rad(latitude)) *
                  sin(rad(city2->latitude)) +
                  cos(rad(latitude)) *
                  cos(rad(city2->latitude)) *
                  cos(rad(longitude) -
                      rad(city2->longitude))) * R;
} //calcDistance

double rad(double degrees)
{
  double radians = 0;
  
  radians = degrees * (M_PI / 180);
  
  return radians;
} //rad()

//This function clears the memory allocated to an individual city
City::~City()
{
  if (name == NULL || strcmp(name, "\0") == 0)
  {
    delete name;
  } //deletes name
  
  if (state == NULL || strcmp(state, "\0") == 0)
  {
    delete state;
  } //Deletes state
    
  //cout << "Deleting city\n";
  strcpy(airport, "%%%");
  name = NULL; //Sets name pointer to NULL
  state = NULL; //Sets state pointer to NULL
  

} //deallocate

void City::setAirport(const char* airpor)
{
  //Copies the user input to the temp airport's airport
  strcpy(airport, airpor);
  
  return;
} //setAirport

bool City::operator==(const City userCity) const
{
  if (name == NULL)
  {
    if (strcmp(airport, userCity.airport) == 0)
    {
      return true;
    } //If the names are the same, they are equal
    else //If the names are not the same, they are not equal
    {
      return false;
    } //If the city names are not the same, they are not the same city
  } //If there is no info for the name, compare airports
  
  if (strcmp(name, userCity.name) == 0 && strcmp(state, userCity.state) == 0)
  {
    return true;
  } //If the names and states are the same, they are equal
  else //If the names are not the same, they are not equal
  {
    return false;
  } //If the city names are not the same, they are not the same city
  
} //isEqual

void City::copyLocation(City* userCity) const
{
  strcpy(userCity->airport, airport);
  
  userCity->name = new char[strlen(userCity->name) + 1];
  strcpy(userCity->name, name);
  
  userCity->latitude = latitude;
  
  userCity->longitude = longitude;
  

  return;
} //copyLocation

//This function reads the values from the CSV file into the city
void City::storeCSV(char* nam, char* stat, const int pop)
{
  if (name == NULL || strcmp(name, "\0") == 0)
  {
    delete name;
  } //Deletes the last name
  
  if (state == NULL || strcmp(name, "\0") == 0)
  {
    delete state;
  } //Deletes state memory
  //Allocates memory for the name
  name = new char[strlen(nam) + 1];
  strcpy(name, nam); //Copies city name info
  
  //Allocates memory for the state
  state = new char[strlen(stat) + 1];
  strcpy(state, stat); //Copies state info
  
  population = pop; //Copies population info
  
  
} //storeCSV

//This function copies city info from one city to another
void City::copyTempInfo(City* copyFrom)
{
  //Copies airport info
  strcpy(airport, copyFrom->airport);
  
  //Copies name info
  name = new char[strlen(copyFrom->name) + 1];
  strcpy(name, copyFrom->name);
  
  //Copies state info
  state = new char[strlen(copyFrom->state) + 1];
  strcpy(state, copyFrom->state);
  
  latitude = copyFrom->latitude;
  longitude = copyFrom->longitude;
  //population = copyFrom->population;
  
  return;
} //copyTempInfo

//This function copies info from the city stored in the array of cities to the city used by run()
void City::copyInfo(City* userCity)
{

  strcpy(userCity->airport, airport);
  
  userCity->name = new char[strlen(name) + 1];
  strcpy(userCity->name, name);
  
  userCity->state = new char[strlen(state) + 1];
  strcpy(userCity->state, state);
  
  userCity->latitude = latitude; //Copies latitude info
  
  userCity->longitude = longitude; //Copies longitude info
  
  userCity->population = population; //Copies population info
  
  return;
} //copyInfo()

int City::calcPassengers(City* city2)
{
  double passengers = 0;
  double pop1 = population;
  double pop2 = city2->population;
  passengers = (double)((pop1 / 2500000000U) * pop2);

  return (int)passengers;
} //calcPassengers

void City::print(City* city2, int passengers, int distance)
{
  cout << passengers << " passengers";
  cout << " fly the " << (int)distance << " miles from\n";
  cout << name << ", ";
  cout << state;
  cout << " to " << city2->name;
  cout << ", " << city2->state << ".\n";
  
  
  return;
} //print()

City& City::operator=(const City &rhs)
{
  if (this == &rhs)
  {
    return *this;
  } //If it is the same, equal
  
  if (name)
  {
    delete []name;
  } //If the name has been made, delete it
  
  if (state)
  {
    delete []state;
  } //If the state has been made, delete it
  
  latitude = rhs.latitude;
  longitude = rhs.longitude;
  population = rhs.population;
  
  if (rhs.name) //If there is a name
  {
    name = new char[strlen(rhs.name) + 1];
    strcpy(name, rhs.name);
  } //Copies name
  
  if (rhs.name)
  {
    state = new char[strlen(rhs.state) + 1];
    strcpy(state, rhs.state);
  } //Copies name
  
  strcpy(airport, rhs.airport);
  
  return *this;
} //=

ifstream& operator >> (ifstream& csvFile, City &rhs)

{
  char * pch; //Pointer character to store string tokens
  char str[99] = "\0"; //String to store line of CSV File
  char name[100] = "\0"; //Stores city name
  char state[100] = "\0"; //Stores state
  int pop = 0; //Stores city population
  
  csvFile.getline(str, 100);
  
  pch = strtok (str, ",,"); //Splits line at commas
  
  while (pch != NULL)
  {
    strcpy(name, pch);
    pch = strtok (NULL, ",,");
    
    strcpy(state, pch);
    pch = strtok (NULL, ",,");
    pop = atoi(pch);
    pch = strtok (NULL, ",,");
    pch = strtok (NULL, ",,");
    
  } //While the pointer char is not NULL
  
  rhs.storeCSV(name, state, pop);
  
  return csvFile;
} //Inserts info
