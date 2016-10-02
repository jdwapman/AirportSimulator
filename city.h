

#ifndef __AirlinePerfect__city__
#define __AirlinePerfect__city__

#include <fstream>

using namespace std;

class City
{
  double latitude;
  double longitude;
  char* name;
  char* state;
  char airport[4];
  int population;
  
public:
  
  City();
  
  ~City();
  
  char* getName();
  
  char* getState();
  
  void printList();
  
  void initialize();
  
  void readAirport(char* line, char* stat);
  
  void deallocate();
  
  void setAirport(const char* airpor);
  
  bool hasAirport();
  
  void copyLocation(City* userCity) const;
  
  void removeFrontSpace(char* nam);
  
  void storeCSV(char* nam, char* stat, const int pop);
  
  void copyTempInfo(City* copyFrom);
  
  void copyInfo(City* userCity);
  
  void calcDistance(const City* city2, int* d) const;
  
  int calcPassengers(City* city2);
  
  void print(City* city2, int passengers, int distance);
  
  void clearTempCity(int totalCities);
  
  City& operator=(const City &rhs);
  
  bool operator == (const City userCity) const;
  
  friend ifstream& operator >> (ifstream& csvFile, City &rhs);

}; //City

  double rad(double degrees);



#endif

