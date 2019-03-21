#include "./router.h"
#include <exception>

Router::Router(std::string ven, int mod, int id, int portNum, std::string prot)	: Device(ven, mod, id, prot) {
	status = PortStatus::ON;

	if (portNum > 0 && portNum <= MAX_PORTS_ROUTER)	{
		ports.resize(portNum);
		for (int i = 0; i < (portNum - 1); i++) ports.at(i) = PortStatus::OFF; 	
	}	else {
		std::cerr 
      << "Number of ports entered is greater than the maximum or less than the minimum. "
			<< "Number of ports set to "<< MAX_PORTS_ROUTER << std::endl;
		ports.resize(MAX_PORTS_ROUTER);
		for (int i = 0; i < MAX_PORTS_ROUTER; i++) ports.at(i) = PortStatus::OFF; 
	}
}


void Router::portPower(unsigned int port, bool s) {
	try {
		if (port == 0) {
			for (int i = 0; i < ports.size(); i++) ports.at(i) = s;
			std::cout << "All ports set to inputted status." << std::endl << std::endl;
		}	else if (port > 0 && port <= ports.size()) {
			ports.at(port - 1) = s;
		} else {
			throw "Please enter a valid port number";
		}
	}	catch (std::string ex) {
		std::cerr << "ERR: " << ex << std::endl;
		std::cout << "Port: ";
		std::cin >> port;
		ENDL

		std::cout << "Status: ";
		std::cin >> s;
		ENDL

		portPower(port, s);
	}
}

void Router::devicePower(bool s) {
	char input; 
	bool port_status;
	Device::devicePower(s);

	try	{
		if (status == PortStatus::ON && s == PortStatus::OFF) {
			for (int i = 0; i < ports.size(); i++) {
				port_status = ports.at(i);
				if (port_status == PortStatus::ON) break;
			}

			if (port_status == PortStatus::OFF) {
				devicePower(OFF); 
				std::cout << "Device shutdown successfuly.\n";
			} else {
				throw "Not all ports are set to off.";
			}
		}
	}	catch (std::string ex) {
		std::cerr << ex
			<< "Continue to power device off? "
			<< "(Doing so will shut all ports off)\n"
			<< "Enter y or n: ";

	input:
		std::cin >> input;
		switch (input) {
		case 'y': 
			portPower(0, PortStatus::OFF); 
			setStatus(PortStatus::OFF);
			std::cout << "Device shutdown successfuly.\n";
			break;
		case 'n':
			std::cout << "Device will not be shutdown.\n";
			break;
		default: 
			std::cerr << "Please enter a valid input.\n";
			goto input; 
			break;
		}
	}
}

void Router::print() const {
	Device::print();
	
	for (int i = 0; i < ports.size(); i++)
	{
		if (ports.at(i) == PortStatus::OFF)	{
			std::cout << "Port " << i + 1 << " Status: OFF" << std::endl;
		}	else {
			std::cout << "Port " << i + 1 << " Status: ON" << std::endl;
		}		 
	}
	for(int i = 0; i < 3; i++) ENDL;
}

void Router::setPorts(unsigned int num) {
	if (num == ports.size()) {
		std::cerr << num << " ports already exist.\n";
	}	else if (num > 0 && num < ports.size())	{
		ports.resize(num);
		std::cout << "Number of ports changed to " << num << ".\n";
	}	else if (num > ports.size() && num <= MAX_PORTS_ROUTER)	{
    int prevSize = ports.size();
		ports.resize(num);
    for (int i = prevSize; i < (num - 1); i++) ports.at(i) = PortStatus::OFF; 
		std::cout << "Number of ports changed to " << num << ".\n";
    std::cout << "Setting new ports to OFF. \n";
	}	else {
		std::cerr << "Error: Number of ports inputted is invalid (Under 0 or over 16).\n";
	}
}

void Router::initialize() {
	try	{
		Router empty; 
		std::fstream RAF("../../assets/routers.dat", std::ios::out | std::ios::binary); //fstream object that opens the routers.dat file
		if (!RAF.is_open())	{
			throw("File could not be opened."); 
		}

		for (int i = 0; i < NUM_RECORDS; i++) {
			RAF.seekp(i * sizeof(Router)); 
			RAF.write(reinterpret_cast<const char*>(&empty), sizeof(Router));
		}
		RAF.close();
	}	catch (std::string ex) {
		std::cerr << "ERR: " << ex << std::endl; 
		exit(1); 
	}
}

void Router::deleteRouter(int i) {
	try {
		Router temp;
		std::fstream RAF("../../assets/routers.dat", std::ios::in | std::ios::out | std::ios::binary);
		if(!RAF.is_open()) {
			throw ("File could not be opened.");
		}
		RAF.seekp(i * sizeof(Router));
		RAF.write(reinterpret_cast<const char*>(&temp), sizeof(Router));
		RAF.close();
	} catch (std::string ex) {
		std::cerr << "ERR: " << ex << std::endl;
	}
}

void Router::updateRouter(Router &r, int i) {
	try {
		std::fstream RAF("../../assets/routers.dat", std::ios::in | std::ios::out | std::ios::binary);
		if(!RAF.is_open()) {
			throw ("File could not be opened.");
		}
		RAF.seekp(i * sizeof(Router));
		RAF.write(reinterpret_cast<const char*>(&r), sizeof(Router));
		RAF.close();
	} catch (std::string ex) {
		std::cerr << "ERR: " << ex << std::endl;
	}
}

Router Router::getRouter(int i) {
	try {
		Router temp;
		std::fstream RAF("../../assets/routers.dat", std::ios::in | std::ios::out | std::ios::binary);
		if(!RAF.is_open()) {
			throw ("File could not be opened.");
		}
		RAF.seekg(i * sizeof(Router));
		RAF.read(reinterpret_cast<char*>(&temp), sizeof(Router));
		RAF.close();
		return temp;
	} catch (std::string ex) {
		std::cerr << "ERR: " << ex << std::endl;
	}
}

void Router::printRouters() {
	for (int i = 0; i < NUM_RECORDS; i++) {
		Router r = getRouter(i);
		r.print();
	}
}

void Router::printRouter(int i) {
	if (i < 0 && i >= NUM_RECORDS) {
		throw("Invalid index selected");
	}
	Router r = getRouter(i);
	r.print();
}

