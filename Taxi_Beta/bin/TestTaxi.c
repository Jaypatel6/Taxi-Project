#include <stdio.h>
#include <stdlib.h>
#include "Taxi.h"
#include "Reader.h"

int main()
{

 /*===========linked list test==========*/
 printf("\n=====Linked List Test=====\n");
 TaxiStandList *list = MakeTaxiStandList();
 
 AddTaxiStandEntry(list, 2, 10);
 AddTaxiStandEntry(list, 8, 6);
 printf("list location:%d\n", list->first->next->stand->location);
 AddTaxiStandEntry(list, 4, 1);

 int totalTaxis = list->totalTaxis; 
 Taxi *taxis = malloc(totalTaxis*sizeof(Taxi));
 Taxi *fleet = MakeTaxiFleet(list, taxis);
  
 printf("TEST %d\n", fleet[11].location);
 int i; 
 for(i = 0; i < list->totalTaxis;i++)
 {
  printf("%d, %d\n", fleet[i].location, fleet[i].taxiID);
 }
 
 /*==========linked list test==========*/

 
 /*==========Setter function test==========*/
 printf("\n=====Setter Function Test=====\n");
 SetLocation(fleet, 0, 1);
 SetPickup(fleet, 1, 2);
 SetDestination(fleet, 2, 500); 
 printf("%d\n",fleet[0].location); 
 printf("%d\n",fleet[1].pickup); 
 printf("%d\n",fleet[2].destination); 
 /*==========Setter function test==========*/

/*==========Routing functions test==========*/
 printf("\n=====Routing functions test=====\n");
 int j, total, counter;
 counter =0; 
 Map Irvine;
 Map map = Reader(Irvine); 
 total = map.x * map.y;
 for(i = 0; i < map.y; i++)
 {
  for(j = 0; j< map.x; j++)
  {
   printf("%c", map.arr[counter]);
   counter++;
  }
  printf("\n");
 }
 printf("%d\n", map.x);

 SetLocation(fleet, 1, 0);
 SetPickup(fleet,1, 16);
 
 DeleteTaxiStandList(list);
 DeleteTaxiFleet(fleet); 


 return 0;


}
