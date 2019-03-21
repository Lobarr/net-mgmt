#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "../router/router.h"
#include "../switch/switch.h"

enum MenuChoices {
  ROUTER = 1, 
  SWITCHES = 2, 
  EXIT = 8
};

enum DeviceChoices { 
  INIT = 1, 
  UPDATE = 2, 
  DEL = 3, 
  PRINT = 4, 
  PRINTALL = 5, 
  BACK = 8 
};

enum DeviceUpdateChoices { 
  VEN = 1, 
  PROT = 2, 
  MODEL = 3, 
  ID = 4, 
  STATUS = 5, 
  PORTNUM = 6, 
  SVI = 7, 
  CONT = 8 
};

class Menu {
public:
  static void main();
  static void routers();
  static void updateRouter(int i);
  static void switches();
  static void updateSwitch(int i);
};

#endif