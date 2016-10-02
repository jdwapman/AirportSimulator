//
//  CityList.h
//  AirlinePerfect
//
//  Created by Jonathan Wapman on 5/6/15.
//  Copyright (c) 2015 Jonathan Wapman. All rights reserved.
//

#ifndef __AirlinePerfect__CityList__
#define __AirlinePerfect__CityList__

#include <iostream> //IO library. Used to allow NULL
#include "city.h" //Includes city class

class CityList; //Forward declaration of list class


class cityNode
{
  City data;
  cityNode* next;
 
  cityNode(const City dat, cityNode *hea, cityNode *pre);
  
  friend class CityList;
}; //ListNode



class CityList
{
  cityNode* head;
  
  cityNode* tail;
  
  static int count;
  
public:
  
  CityList();
  
  CityList& operator +=(const City &rhs);
  
  CityList& operator -=(const City &rhs);
  
  City& operator [](const int index);
  
  City& operator [](const int index) const;
  
  void setCount(int coun);
  
  const static int getCount();
  
  ~CityList();
  
}; //List

#endif
