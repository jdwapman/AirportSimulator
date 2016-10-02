//
//  CityList.cpp
//  AirlinePerfect
//
//  Created by Jonathan Wapman on 5/6/15.
//  Copyright (c) 2015 Jonathan Wapman. All rights reserved.
//

#include "citylist.h"

int CityList::count = 0;

CityList::CityList()
{
  head = NULL;
  tail = NULL;
} //Initializer

cityNode::cityNode(const City dat, cityNode * hea, cityNode *tai)
{
  data = dat;
  next = NULL;
  
} //cityNode constructor

CityList::~CityList()
{
  cityNode *ptr;
  
  for (ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  }// Loops through all elements of list
  
} //Destructor

//Overloaded operator for the city list, used to add new cities

CityList& CityList::operator+=(const City &rhs)
{
  cityNode *ptr, *prev = NULL; //Pointers to loop through cities
  
  for (ptr = head; ptr; ptr = ptr->next)
  {
    prev = ptr;
  } //Sets the previous pointer to the tail
  
  if (prev == NULL) //if there is no prev city (start of list)
  {
    head = tail = new cityNode(rhs, head, tail);
  } //If at beginning of list
  else //If not at beginning of list
  {
    tail = new cityNode(rhs, head, tail); //Makes new city
    prev->next = tail; //Sets last next to new city
  } //If not at beginning of list
  
  return *this;
} //Appends new city to end of list

CityList& CityList::operator-=(const City &rhs)
{
  cityNode *ptr, *prev = NULL;
  
  for (ptr = head; ptr; ptr = ptr->next)
  {
    
    if (rhs == ptr->data) //If the data matches
    {
      if (prev != NULL) //If it's not the first entry
      {
        if (ptr == tail) //If last entry
        {
          tail = prev;
        } //If the data is the last entry
        
        prev->next = ptr->next;
        break; //Exits loop
      } //If not at beginning or end of list
      else //If the data is the beginning of the loop
      {
        head = ptr->next; //Moves head to next data
      } //If data is the beginning of the loop
      
      delete ptr; //Deletes data
      break;
    } //If matching data is found
    
    prev = ptr;
  } //Loops through all list entries
  
  setCount(getCount() - 1);
  return *this;
} //Removes city

City& CityList::operator[](const int index)
{
  cityNode* ptr; //Marks location in loop
  int i = 0;
  for (ptr = head; ptr; ptr = ptr->next)
  {
    
    if (i == index)
    {
      return ptr->data;
    } //Returns data
    if (i > index)
    {
      cout << i;
      
    } //error
    i++;
  } //Loops through list until it gets to nth entry
  
  return ptr->data; //Should never be used
} //[] Overloaded operator

City& CityList::operator[](const int index) const
{
  cityNode* ptr; //Marks location in loop
  int i = 0;
  for (ptr = head; ptr; ptr = ptr->next)
  {
    
    if (i == index)
    {
      return ptr->data;
    } //Returns data
    i++;
  } //Loops through list until it gets to nth entry
  
  return ptr->data; //Should never be used
} //[] Overloaded operator

void CityList::setCount(int coun)
{
  count = coun;
} //setCount

const int CityList::getCount()
{
  return count;
} //getCount


