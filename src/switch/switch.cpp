#include "./switch.h"

Switch::Switch(std::string ven, int mod, int id, int portNum, std::string prot, bool svi) :Device(ven, mod, id, prot) {
  SVI = svi;
	status = PortStatus::ON;
	if (portNum > 0 && portNum <= MAX_PORTS_SWITCH) {
		ports.resize(portNum);
		for (int i = 0; i < (portNum - 1); i++) ports.at(i) = PortStatus::OFF; 
	}	else {
		std::cerr 
      << "Number of ports entererd is greater than the maximum or less than the minimum. "
			<< "Number of ports set to 24." << std::endl;
		ports.resize(MAX_PORTS_SWITCH);
		for (int i = 0; i < MAX_PORTS_SWITCH; i++) ports.at(i) = PortStatus::OFF; 
	}
}

void Switch::portPower(unsigned int port, bool s) {
	try	{
		if (port == 0) {
			for (unsigned int i = 0; i < ports.size(); i++) ports.at(i) = s;
			std::cout << "All ports set to inputted status." << std::endl << std::endl;
		}	else if (port > 0 && port <= ports.size()) {
			ports.at(port - 1) = s;
		}	else {
			throw "Please enter a valid port number.\n";
		}
	}	catch (std::string ex) {
		std::cerr << ex << std::endl;
		std::cout << "Port: ";
		std::cin >> port;
		ENDL

		std::cout << "Status: ";
		std::cin >> s;
		ENDL

		portPower(port, s);
	}
}

void Switch::print() const {
	Device::print();
	SVI ? std::cout << "SVI Support: Yes" << std::endl : std::cout << "SVI Support: No" << std::endl;	

	for (unsigned int i = 0; i < ports.size(); i++)	{
		if (ports.at(i) == PortStatus::OFF)	{
			std::cout << "Port " << i + 1 << " Status: OFF" << std::endl;
		}	else {
			std::cout << "Port " << i + 1 << " Status: ON" << std::endl;
		}		
	}	
	for (int i = 0; i < 3; i++) ENDL;
}

void Switch::devicePower(bool s) {
	char input; 
	bool port_stat;
	Device::devicePower(s);

	try	{
		if (status == PortStatus::ON && s == PortStatus::OFF)	{
			for (unsigned int i = 0; i < ports.size(); i++) {
				port_stat = ports.at(i);
				if (port_stat == PortStatus::ON) {
					break;
				}
			}

			if (port_stat == PortStatus::OFF)	{
				devicePower(OFF); 
				std::cout << "Device shutdown successfuly.\n";
			}	else {
				throw "Not all ports are set to off.\n";
			}
		}

	}	catch (std::string ex) {
		std::cerr << ex
			<< "Continue to power device off? "
			<< "(Doing so will shut all ports off)\n"
			<< "Enter y or n: ";

	input:
		std::cin >> input;
		switch (input)
		{
		case 'y': 
			portPower(0, OFF); 
			setStatus(OFF);
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

bool Switch::getSVI() const {
	return SVI;
}

void Switch::setSVI(bool svi) {
	SVI = svi;
}

void Switch::setPorts(unsigned int num) {
	if (num == ports.size()) {
		std::cerr << num << " ports already exist.\n";
	}	else if (num < ports.size() && num > 0)	{
		ports.resize(num);
		std::cout << "Number of ports changed to " << num << ".\n";
	}	else if (num > ports.size() && num <= MAX_PORTS_SWITCH) {
    int prevSize = ports.size();
		ports.resize(num);
    for (int i = prevSize; i < (num - 1); i++) ports.at(i) = PortStatus::OFF; 
		std::cout << "Number of ports changed to " << num << ".\n";
    std::cout << "Setting new ports to OFF. \n";
	}	else {
		std::cerr << "Error: Number of ports inputted is invalid (Under 0 or over 24).\n";
	}
}

void Switch::initialize() {
	try	{
		Switch empty;
		std::fstream RAF("../../assets/switches.dat", std::ios::out | std::ios::binary);
		if (!RAF.is_open())	{
			throw "File could not be opened";
		}

		for (int i = 0; i < NUM_RECORDS; i++) {
			RAF.seekp(i * sizeof(Switch)); 
			RAF.write(reinterpret_cast<const char*>(&empty), sizeof(Switch)); 
		}
		RAF.close(); 
	}	catch (std::string ex) {
		std::cerr << "ERR: " << ex << std::endl; 
		exit(1); 
	}
}

void Switch::deleteSwitch(int i) {
	try {
		Switch temp;
		std::fstream RAF("../../assets/switches.dat", std::ios::in | std::ios::out | std::ios::binary);
		if(!RAF.is_open()) {
			throw ("File could not be opened.");
		}
		RAF.seekp(i * sizeof(Switch));
		RAF.write(reinterpret_cast<const char*>(&temp), sizeof(Switch));
		RAF.close();
	} catch (std::string ex) {
		std::cerr << "ERR: " << ex << std::endl;
	}
}

void Switch::updateSwitch(Switch &s, int i) {
	try {
		std::fstream RAF("../../assets/switches.dat", std::ios::in | std::ios::out | std::ios::binary);
		if(!RAF.is_open()) {
			throw ("File could not be opened.");
		}
		RAF.seekp(i * sizeof(Switch));
		RAF.write(reinterpret_cast<const char*>(&s), sizeof(Switch));
		RAF.close();
	} catch (std::string ex) {
		std::cerr << "ERR: " << ex << std::endl;
	}
}

Switch Switch::getSwitch(int i) {
	try {
		Switch temp;
		std::fstream RAF("../../assets/switches.dat", std::ios::in | std::ios::out | std::ios::binary);
		if(!RAF.is_open()) {
			throw ("File could not be opened.");
		}
		RAF.seekg(i * sizeof(Switch));
		RAF.read(reinterpret_cast<char*>(&temp), sizeof(Switch));
		RAF.close();
		return temp;
	} catch (std::string ex) {
		std::cerr << "ERR: " << ex << std::endl;
	}
}


void Switch::printSwitches() {
	for (int i = 0; i < NUM_RECORDS; i++) {
		Switch s = getSwitch(i);
		s.print();
	}
}

void Switch::printSwitch(int i) {
	if (i <= 0 && i > NUM_RECORDS) {
		throw("Invalid index selected");
	}
	Switch s = getSwitch(i);
	s.print();
}