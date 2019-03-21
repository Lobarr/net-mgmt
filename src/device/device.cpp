#include "./device.h"

Device::Device(std::string ven, int mod, int id, std::string prot) :vendor(ven), model(mod), ID(id), protocol(prot) {
	status = PortStatus::ON;
}


void Device::devicePower(bool s) {
	if ((status == PortStatus::ON && s == PortStatus::ON) || (status == PortStatus::OFF && s == OFF)) {
		std::string power = s == PortStatus::ON ? "On" : "Off";
		std::cout << "Power already set to " << power << ".\n";
	}	
} 

void Device::print() const {
	std::cout << "Vendor: " << vendor << std::endl
		<< "Model " << model << std::endl
		<< "ID: " << ID << std::endl
		<< "Protocol: " << protocol << std::endl;		
	status == PortStatus::OFF ? std::cout << "Power Status: OFF" << std::endl : std::cout << "Power Status: ON" << std::endl;
} 


std::string Device::getVendor() const {
	return vendor;
}

std::string Device::getProtocol() const {
	return protocol;
}

int Device::getModel() const {
	return model;
}

int Device::getID() const {
	return ID;
}

bool Device::getStatus() const {
	return status;
}

//mutator functions 
void Device::setVendor(const std::string v) {
	vendor = v;
}

void Device::setProtocol(const std::string p) {
	protocol = p;
}

void Device::setModel(const int m) {
	model = m;
}

void Device::setID(int id) {
	ID = id;
}

void Device::setStatus(bool input) {
	status = input;
}

std::vector<bool> Device::getPorts() const {
	return ports;
}