#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

enum PortStatus { 
  OFF = false, 
  ON = true 
};

const int NUM_RECORDS = 10;

#define ENDL std::cout << std::endl;

class Device {
public:
	Device(std::string vendor, int model, int id, std::string protocol);  

	virtual void portPower(); 
	virtual void devicePower(bool s); // turns off or on the device 
	virtual void print() const; // prints device information

	std::string getVendor() const;
	std::string getProtocol() const;
	int getModel() const;
	int getID() const;
	bool getStatus() const;
	std::vector<bool> getPorts() const;
	void setVendor(const std::string v);
	void setProtocol(const std::string p);
	void setModel(const int m);
	void setID(int id);
	void setStatus(bool input);

protected:
	std::string vendor; // vendor of device
	std::string protocol; // protocol running on device
	int model; // model of device
	int ID; // record number
	bool status; // stores power status (on/off), default on in constructor
	std::vector<bool> ports; // default to off (false) in constructor
};

#endif