
#ifndef ROUTER_H
#define ROUTER_H

#include "../device/device.h"

const int MAX_PORTS_ROUTER = 16;

class Router : public Device {
public:
	Router(std::string vend = "", int mod = 0, int id = 0, int portNum = 16, std::string prot = "");
  void portPower(unsigned int port, bool s); // switches on or off a port
	void devicePower(bool s); // turn device on/off, all ports must be off before
	void print() const; // prints device information
	void setPorts(unsigned int num); // used to set number of ports
	static void initialize(); //initialize routers.dat to 10 empty records
	static void deleteRouter(int i); // delete's router from routers.dat
	static void updateRouter(Router &r, int i);
	static Router getRouter(int i);
	static void printRouters();
	static void printRouter(int i);
};

#endif