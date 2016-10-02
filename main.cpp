#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include "citylist.h"
#include "plane.h"

using namespace std;


void calcAirportTraffic(const CityList& cities);

void readAirports();

void cleanCities(CityList& cities);

int findAirport(const char* airport, const CityList& cities);

void readCSV();

int calcPassengers(int cityNum1, int cityNum2, const CityList& cities);

void calcDistance(const int c1, const int c2, int* d, const CityList& cities);

void printResults(int cityNum1, int cityNum2, const CityList& cities);

void printList(const CityList& cities);

void readCities(ifstream& csvFile, CityList& cities);

void copyTempInfo(City* tempCities);

City getCity(const int cityNum, const CityList& cities);

//This function allocates memory for the initial city array and calls a function to
//Initialize each individual city

//This function reads values from AirportsLL
void readAirports(CityList& cities)
{
  City tempCity;
  char line[100];
  char stat[100];
  ifstream airportFile("airportLL.txt");
  airportFile.getline(line, 100);
  
  while(!airportFile.eof()) //While not at the end of a file
  {
    airportFile.getline(line, 100);
    
    if (strncmp(line, "[", 1) != 0) //If it is a state line
    {
      if (isalpha(line[0]))
      {
        strcpy(stat, line);
      } //If the line starts with a letter
    } //If the line does not start with a bracket
    
    if (strncmp(line, "[", 1) == 0) //If it is an airport line
    {
      tempCity.readAirport(line, stat);
      
      for (int i = 0; i < cities.getCount(); ++i)
      {
        if (tempCity == cities[i]) //CHANGE TO ==
        {
          cities[i].copyTempInfo(&tempCity);
        } //If the cities are equal, copy the info
      } //Loops through all cities in array
    } //If the line has city info
  } //While not at the end of the file
  
  airportFile.close();
} //readAirports()

void calcDistance(int c1, int c2, int* d, const CityList& cities)
{
  cities[c1].calcDistance(&cities[c2], d);
} //calDistance()

void copyTempInfo(City* tempCities, CityList& cities)
{
  int i = 0;
  int j = 0;
  //Copies all city info to the temp city array
  for (i = 0; i < cities.getCount(); ++i)
  {
    if (cities[i].hasAirport() == true) //If the city has an airport
    {
      tempCities[j].copyTempInfo(&cities[i]);
      
      ++j; //Increments j, the counter for the temp city array
    } //If the city has an airport, copy the info
  } //Loops through all cities
  
  return;
} //copyTempInfo

City getCity(const int cityNum, const CityList& cities)
{
  return cities[cityNum];
} //getCity()

void cleanCities(CityList& cities)
{
  int i = 0;
  int numAirports = 0;
  int numCleared = 0;
  
  for (i = 0; i < cities.getCount(); ++i) //Loops through all the cities
  {
    
    if (cities[i].hasAirport() == true)
    {
      numAirports++;
    } //If there is no airport
  } //Loops through all cities

  
  for (i = 0; i < numAirports; ++i) //Loops through all the cities
  {
    
    if (cities[i].hasAirport() == false)
    {
      cities -= cities[i];
      numCleared++;
      i = 0;
      cities.setCount(cities.getCount() - 1);
    } //If there is no airport
  } //Loops through all cities
  

  cities.setCount(numAirports);
  return;
} //cleanCities()

int findAirport(const char* airport, const CityList& cities)
{
  int i = 0; //Counter variable
  City tempCity;
  
  //Sets the temporary city variable to have the user's airput info
  tempCity.setAirport(airport);
  
  for (i = 0; i < cities.getCount(); ++i)
  {
    if (tempCity == cities[i])
    {
      cities[i].copyInfo(&tempCity);
      
      return i;
    } //Checks if airports match
  } //searches through all the city airports to see if they match
  
  //tempCity.deallocate();
  
  return -1; //Returns false
  
} //findAirport()

//Reads the csv file and gets count of how many cities there are
void readCSV(CityList& cities)
{
  char line[100];
  ifstream csvFile("citypopulations.csv");
  
  cities.setCount(0); //Sets the initial count of cities to 0
  
  //This loop reads the csv file and reallocates memory until it reaches end of file
  
  while (!csvFile.eof())
  {
    csvFile.getline(line, 100);
    cities.setCount(cities.getCount() + 1);
  } //While not at end of file
  
  cities.setCount(cities.getCount() - 1); //Accounts for 2 newlines eof
  
  readCities(csvFile, cities); //Reads from CSV
  csvFile.close();
  return;
} //readCSV()

//This function gets individual values from the CSV file
void readCities(ifstream& csvFile, CityList& cities)
{
  int i = 0; //Counter variable to loop through cities
  csvFile.clear();
  csvFile.seekg(0); //Goes to beginning of file
  City tempCity;
  
  for (i = 0; i < cities.getCount(); ++i)
  {

    csvFile >> tempCity;
    
    cities += tempCity;
  } //Loops through cities in array
  
  return;
} //readCities


void printResults(int city1, int city2, const CityList& cities)
{
  int distance = 0;
  int people = 0;
  
  //Gets distance between cities
  calcDistance(city1, city2, &distance, cities);
  
  //Gets number of passengers that fly between cities
  people = calcPassengers(city1, city2, cities);
  
  if (distance < 100)
  {
    people = 0;
  } //If the distance is less thtan 100, 0 fly
  
  cities[city1].print(&cities[city2], people, distance);
  
  return;
} //printResults()

int calcPassengers(int city1, int city2, const CityList& cities)
{
  return cities[city1].calcPassengers(&cities[city2]);
} //calcPassengers()

void calcAirportTraffic(const int cityNum, const CityList& cities)
{
  int distance = 0;
  int people = 0;
  int totalPeople = 0;
  
  for (int i = 0; i < cities.getCount(); ++i)
  {
    if (cityNum == i)
    {
      continue;
    } //Checks to see if the looping city is the picked city
    
    people = calcPassengers(cityNum, i, cities); //Gets the number of passengers
    cities[cityNum].calcDistance(&cities[i], &distance);
    
    if (distance < 100)
    {
      people = 0;
    } //If the distance is less that 100, no people fly
    
    totalPeople = totalPeople + people;
    
    cout << cities[i].getName(); //Prints name
    cout << ", ";
    cout << cities[i].getState(); //prints state
    cout << ": ";
    cout << people;
    cout << "\n";
  } //loops though all cities to calculate the passengers
  
  cout << "Total passengers: " << totalPeople << "\n";
  return;
} //calcAirportTraffic

void printList(const CityList& cities)
{
  for (int i = 0; i < cities.getCount(); ++i)
  {
    cities[i].printList();
  } //Loops through cities to print them
  
  return;
} //printList()

//END OLD VECTOR CODE

void getUserInput(char* input1, char* input2)
{
  //Asks the user to enter two airports
  cout << "\nPlease enter two airport abbreviations (XXX XXX): ";
  cin >> input1 >> input2; //Scans the user's input
  
  return;
} //getUserInput

//Gets the user's input
int getChoice()
{
  int choice = 0;
  
  cout << "\nFlight Simulator Menu\n";
  cout << "0. Done.\n";
  cout << "1. Determine distance and passengers between two airports.\n";
  cout << "2. Determine all traffic from one airport.\n";
  cout << "3. Display planes information.\n";
  cout << "4. Add plane information.\n";
  cout << "5. Determine best plane between two airports.\n";
  cout << "\n";
  cout << "Your choice (0 - 5): ";
  
  cin >> choice; //Gets user input
  cin.ignore(); //Ignores newline

  return choice;
  
}//getChoice

//runs UI to calculate passengers to and from a city
void calcAirportTraffic(const CityList& cities)
{
  char input[80] = "\0";
  int cityNum = -1;
  
  cout << "\nPlease enter an airport abbreviation (XXX): ";
  
  cin >> input;
  
  if (findAirport(input, cities) == -1)
  {
    cout << input << " is not a valid airport.\n";
    return;
  } //If the airport is not found
  
  cityNum = findAirport(input, cities);
  
  calcAirportTraffic(cityNum, cities);
  
  return;
} //calcAirportTraffic()

void twoAirports(const CityList& cities)
{
  char input1[80] = "airport";
  char input2[80] = "airport";
  int cityNum1 = 0;
  int cityNum2 = 0;

  getUserInput(input1, input2); //Gets user input
    
    if (findAirport(input1, cities) == -1 || findAirport(input2, cities) == -1)
    {
      if (findAirport(input1, cities) == -1)
      {
        cout << input1 << " is not a valid airport.\n";
        
        if (findAirport(input2, cities) == -1)
        {
          cout << input2 << " is not a valid airport.\n";
        } //If the second airport is not found
        
        return;
      } //If the airport is not found
      
      if (findAirport(input2, cities) == -1)
      {
        cout << input2 << " is not a valid airport.\n";
        return;
      } //If the airport is not found
    } //If the airports are not valid
    
    cityNum1 = findAirport(input1, cities); //Finds 1st airport
    cityNum2 = findAirport(input2, cities); //Finds 2nd airport
    printResults(cityNum1, cityNum2, cities); //Prints results
} //two Airports()

//Displays information about a plane
void displayPlaneInformation(const Plane planes[10], CityList& cities, int num)
{
  cout << "\nPlane Information\n";
  cout << left << setw(12) << "Name";
  cout << left << setw(6) << "Pass.";
  cout << left << setw(6) << "Range";
  cout << left << setw(6) << "Speed";
  cout << left << setw(7) << "Fuel";
  cout << left << setw(6) << "MPG";
  cout << left << setw(6) << "$/mi";
  cout << left << setw(12) << "Price * 10^6";
  cout << "\n";
  
  for (int i = 0; i < num; ++i)
  {
    cout << planes[i];
  } //Loops through all airplanes
  
} //displayPlaneInformation()

//Adds info about a plane to the file
void addPlaneInformation(Plane planes[10], const int numPlanes)
{
  ofstream planeFile("planes.dat", ios::out | ios::app | ios::binary);
  char name[12];
  int passengers;
  int range;
  int speed;
  int fuel;
  int price;
  int num = numPlanes - 1;

  
  cout << "Name: ";
  cin >> name;
  cin.ignore(); //Ignores newline
  planes[num].setName(name);
  cout << "Passengers: ";
  cin >> passengers;
  planes[num].setPassengers(passengers);
  cout << "Fuel capacity (in U.S. gallons): ";
  cin >> fuel;
  planes[num].setFuel(fuel);
  cout << "Range (in miles): ";
  cin >> range;
  planes[num].setRange(range);
  cout << "Speed (in mph): ";
  cin >> speed;
  planes[num].setSpeed(speed);
  cout << "Price: ";
  cin >> price;
  planes[num].setPrice(price);
  
  planes[num].writePlane(&planeFile);
  
  planeFile.close();
} //addPlaneInformation()

void printBestPlaneInfo()
{
  cout << left << setw(11) << "Passengers";
  cout << left << setw(7) << "Miles";
  cout << left << setw(6) << "Trips";
  cout << left << setw(10) << "Name";
  cout << left << setw(4) << "Cost" << "\n";
} //printBestPlaneInfo()

int findBestPlane(const int numPlanes, double totalCost[10])
{
  int bestPlane = 0;
  
  for (int i = 1; i < numPlanes; ++i)
  {
    if (totalCost[i] < totalCost[bestPlane])
    {
      bestPlane = i;
    } //If the current plane is cheaper than the last one
  } //Loops through planes
  
  return bestPlane;
} //findBestPlane

void determineBestPlane(const CityList& cities, const Plane planes[10], const
                        int numPlanes)
{
  char input1[4]; //Input 1
  char input2[4]; //Input 2
  int cityNum1;
  int cityNum2;
  double totalCost[10]; //Stores cost of each plane
  int bestPlane = 0; //Sets the best plane to be the first plane
  int distance = 0;
  int passengers = 0;
  getUserInput(input1, input2); //Gets the user's input
  cityNum1 = findAirport(input1, cities); //Finds 1st airport
  cityNum2 = findAirport(input2, cities); //Finds 2nd airport
  calcDistance(cityNum1, cityNum2, &distance, cities);
  passengers = calcPassengers(cityNum1, cityNum2, cities);
  
  for (int i = 0; i < numPlanes; ++i)
  {
    totalCost[i] = planes[i].totalCost(cities, distance, passengers);
  } //loops through cities
  
  bestPlane = findBestPlane(numPlanes, totalCost);
  
  if (totalCost[bestPlane] == 9999999)
  {
    cout << "No planes available\n";
    return;
  } //If invalid plane
  
  printBestPlaneInfo();
  cout << left << setw(11) << passengers;
  cout << left << setw(7) << distance;
  cout << left << setw(6) <<  ceil((double)passengers /
                        (double)planes[bestPlane].getPassengers());
  cout << left << setw(10) << planes[bestPlane].getName();
  cout << left << "$" << setw(3) << totalCost[bestPlane] << "\n";
} //determineBestPlane()

void initializeCosts(int totalCost[10])
{
  for (int i = 0; i < 10; ++i)
  {
    totalCost[i] = 9999999;
  } //Sets total cost to 9999999
} //initializeCosts()


//Runs program
void run(CityList& cities, Plane planes[10], int numPlanes)
{
  
  while(1) //Infinite loop
  {
  
    switch (getChoice())
    {
      case 0:
        return;
        break;
      case 1:
        twoAirports(cities);
        break;
      case 2:
        calcAirportTraffic(cities);
        break;
      case 3:
        displayPlaneInformation(planes, cities, numPlanes);
        break;
      case 4:
        numPlanes++;
        addPlaneInformation(planes, numPlanes);
        break;
      case 5:
        determineBestPlane(cities, planes, numPlanes);
        break;
      default:
        cout << "Your choice must be between 0 and 2. Please try again.\n";
    } //Gets user's input
  } //Infinite loop
  
} //run()

//Loops through all planes to read from the binary file
void readPlanesFile(Plane airplane[10], int* numPlanes)
{
  ifstream planeFile; //File with plane info
  
  planeFile.open("planes.dat", ios::in | ios::binary); //Opens binary file
  
  for (int i = 0; i < 10; ++i)
  {
    airplane[i].readPlane(&planeFile, i);
    
    if (airplane[i].isPlane() == true)
    {
      *numPlanes = *numPlanes + 1;
    } //If the entry is a plane, incrememnt number of planes
  } //Loops through planes
  
  planeFile.close(); //Closes file
  
} //readPlanesFile

int main()
{
  CityList cities; //Declares cityList to hold city info //GOOD
  
  Plane planes[10]; //GOOD
  
  int numPlanes = 0; //Number of planes in the array //GOOD
  
  readCSV(cities); //Reads info from the CSV file //GOOD
  
  readAirports(cities); //Reads airport info into the cityList
  

  
  
  cleanCities(cities); //Removes cities without an airport
  
  readPlanesFile(planes, &numPlanes);
  
  run(cities, planes, numPlanes); //Runs program
  
  return 0; //Ends program
} //main()
