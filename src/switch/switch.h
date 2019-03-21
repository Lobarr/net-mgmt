#ifndef SWITCH_H
#define SWITCH_H

#include "../device/device.h"

const int MAX_PORTS_SWITCH = 24;

class Switch : public Device  {
public:
	Switch(std::string ven = "", int mod = 0, int id = 0, int portNum = MAX_PORTS_SWITCH, std::string prot = "", bool svi = 0);

	void portPower(unsigned int port, bool s);  // turns off or on a port / all ports 
	void devicePower(bool s);  // turns device on/off
	void print() const;  // prints device information
	bool getSVI() const;
	void setSVI(bool svi);
	void setPorts(unsigned int num); // used to set number of ports
	static void initialize(); //initialize switches.dat to 10 empty records
	static void deleteSwitch(int i); // delete's router from routers.dat
	static void updateSwitch(Switch &s, int i);
	static Switch getSwitch(int i);
	static void printSwitches();
	static void printSwitch(int i);
private:
	bool SVI; // switch support for SVI
};

#endif