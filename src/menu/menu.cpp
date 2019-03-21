#include "./menu.h"


void Menu::main() {
  int option = 0;
  menuInput:
  std::cout 
    << "************* MENU *************" << std::endl
    << "1. Router" << std::endl
    << "2. Switces" << std::endl
    << "8. Quit" << std::endl
    << "> "; 
  
  std::cin >> option;
  ENDL

  switch(option) {
    case MenuChoices::ROUTER:
      routers();
      option = 0;
      break;
    case MenuChoices::SWITCHES:
      switches();
      option = 0;
      break;
    case MenuChoices::EXIT:
      exit(0);
    default:
      std::cout << "Please input a valid menu option.\n";
      goto menuInput;
  }
}

void Menu::routers() {
  try {
    int index = 0;
    int option = 0; 

    invalid_input:
    std::cout << "Choose Router Data" << std::endl
      << "Router 1 - 10" << std::endl
      << "> ";
    std::cin >> index;
    ENDL 

    if (index <= 0 && index > NUM_RECORDS) {
      std::cerr << "ERR: Invalid Input" << std::endl;
      goto invalid_input;
    }

    menu_input:
    std::cout << "************* MENU *************" << std::endl
      << "1. Initialize Router" << std::endl
      << "2. Update Router" << std::endl
      << "3. Delete Router" << std::endl
      << "4. Print Router" << std::endl
      << "5. Print ALL Routers" << std::endl
      << "8. Back" << std::endl
      << "> ";
    std::cin >> option;
    ENDL

    switch(option) {
      case DeviceChoices::INIT:
        updateRouter(index-1);
        goto menu_input;
        break;
      case DeviceChoices::UPDATE:
        updateRouter(index-1);
        goto menu_input;
        break;
      case DeviceChoices::DEL:
        Router::deleteRouter(index-1);
        goto menu_input;
        break;
      case DeviceChoices::PRINT:
        Router::printRouter(index-1);
        goto menu_input;
        break;
      case DeviceChoices::PRINTALL:
        Router::printRouters();
        goto menu_input;
        break;
      case DeviceChoices::BACK:
        main();
        break;
      default:
        throw("Invalid input");
        goto menu_input;
        break;
    }
  } catch(std::string ex) {
    std::cerr << "ERR: " << ex << std::endl;
    routers();
  }
}

void Menu::updateRouter(int i) {
  try {
    bool temp_bool;
    int temp_int;
    std::string temp_str;
    int option;

    #define ResetI temp_int = 0;
    #define ResetS temp_str = "";
    #define ResetB temp_bool = false;

    Router buffer = Router::getRouter(i);
    menu_input:
    std::cout << "************* UPDATE RECORD *************" << std::endl
      << "1. Vendor" << std::endl
      << "2. Protocol" << std::endl
      << "3. Model" << std::endl
      << "4. ID" << std::endl
      << "5. Power (true - 1/false - 0)" << std::endl
      << "6. Number of Ports" << std::endl
      << "8. Done " << std::endl 
      << "> ";
    std::cin >> option;
    ENDL

    switch (option)
    {
      case DeviceUpdateChoices::VEN: //passes user input into specified data mutator function
        std::cout << "> ";
        std::cin >> temp_str;
        ENDL
        buffer.setVendor(temp_str);
        ResetS
        goto menu_input;
        break;
      case DeviceUpdateChoices::PROT:
        std::cout << "> ";
        std::cin >> temp_str;
        ENDL
        buffer.setProtocol(temp_str);
        ResetS
        goto menu_input;				
        break;
      case DeviceUpdateChoices::MODEL:
        std::cout << "> ";
        std::cin >> temp_int;
        ENDL
        buffer.setModel(temp_int);
        ResetI
        goto menu_input;
        break;
      case DeviceUpdateChoices::ID:
        std::cout << "> ";
        std::cin >> temp_int;
        ENDL
        buffer.setID(temp_int);
        ResetI
        goto menu_input;
        break;
      case DeviceUpdateChoices::STATUS:
        std::cout << "> ";
        std::cin >> temp_bool;
        ENDL
        buffer.setStatus(temp_bool);
        goto menu_input;
        break;
      case DeviceUpdateChoices::PORTNUM:
        std::cout << "> ";
        std::cin >> temp_int;
        ENDL
        buffer.setPorts(temp_int);
        ResetI
        goto menu_input;
        break;
      case DeviceUpdateChoices::CONT:
        Router::updateRouter(buffer, i);
        std::cout << "File Successfully Updated" << std::endl;
        break;
      default:
        std::cerr << "ERR: Input a valid value" << std::endl;
        goto menu_input;
        break;
    }
  } catch (std::string ex) {
    std::cerr << "ERR: " << ex << std::endl;
    main();
  }
}

void Menu::switches() {
  try {
    int index = 0;
    int option = 0; 

    invalid_input:
    std::cout << "Choose Switch Data" << std::endl
      << "Switch 1 - 10" << std::endl
      << "> ";
    std::cin >> index;
    ENDL 

    if (index <= 0 && index > NUM_RECORDS) {
      std::cerr << "ERR: Invalid Input" << std::endl;
      goto invalid_input;
    }

    menu_input:
    std::cout << "************* MENU *************" << std::endl
      << "1. Initialize Switch" << std::endl
      << "2. Update Switch" << std::endl
      << "3. Delete Switch" << std::endl
      << "4. Print Switch" << std::endl
      << "5. Print ALL Switch" << std::endl
      << "8. Back" << std::endl
      << "> ";
    std::cin >> option;
    ENDL

    switch(option) {
      case DeviceChoices::INIT:
        updateSwitch(index-1);
        goto menu_input;
        break;
      case DeviceChoices::UPDATE:
        updateSwitch(index-1);
        goto menu_input;
        break;
      case DeviceChoices::DEL:
        Switch::deleteSwitch(index-1);
        goto menu_input;
        break;
      case DeviceChoices::PRINT:
        Switch::printSwitch(index-1);
        goto menu_input;
        break;
      case DeviceChoices::PRINTALL:
        Switch::printSwitches();
        goto menu_input;
        break;
      case DeviceChoices::BACK:
        main();
        break;
      default:
        throw("Invalid input");
        goto menu_input;
        break;
    }
  } catch (std::string ex) {
    std::cerr << "ERR: " << ex << std::endl;
    switches();
  }
}

void Menu::updateSwitch(int i) {
  try {
    bool temp_bool;
    int temp_int;
    std::string temp_str;
    int option;

    #define ResetI temp_int = 0;
    #define ResetS temp_str = "";
    #define ResetB temp_bool = false;

    Switch buffer = Switch::getSwitch(i);
    menu_input:
    std::cout << "************* UPDATE RECORD *************" << std::endl
      << "1. Vendor" << std::endl
      << "2. Protocol" << std::endl
      << "3. Model" << std::endl
      << "4. ID" << std::endl
      << "5. Power (true - 1/false - 0)" << std::endl
      << "6. Number of Ports" << std::endl
      << "7. SVI (true - 1/false - 0)" << std::endl
      << "8. Done " << std::endl 
      << "> ";
    std::cin >> option;
    ENDL

    switch (option)
    {
      case DeviceUpdateChoices::VEN: //passes user input into specified data mutator function
        std::cout << "> ";
        std::cin >> temp_str;
        ENDL
        buffer.setVendor(temp_str);
        ResetS
        goto menu_input;
        break;
      case DeviceUpdateChoices::PROT:
        std::cout << "> ";
        std::cin >> temp_str;
        ENDL
        buffer.setProtocol(temp_str);
        ResetS
        goto menu_input;				
        break;
      case DeviceUpdateChoices::MODEL:
        std::cout << "> ";
        std::cin >> temp_int;
        ENDL
        buffer.setModel(temp_int);
        ResetI
        goto menu_input;
        break;
      case DeviceUpdateChoices::ID:
        std::cout << "> ";
        std::cin >> temp_int;
        ENDL
        buffer.setID(temp_int);
        ResetI
        goto menu_input;
        break;
      case DeviceUpdateChoices::STATUS:
        std::cout << "> ";
        std::cin >> temp_bool;
        ENDL
        buffer.setStatus(temp_bool);
        ResetB
        goto menu_input;
        break;
      case DeviceUpdateChoices::PORTNUM:
        std::cout << "> ";
        std::cin >> temp_int;
        ENDL
        buffer.setPorts(temp_int);
        ResetI
        goto menu_input;
        break;
      case DeviceUpdateChoices::SVI:
        std::cout << "> ";
        std::cin >> temp_bool;
        ENDL
        buffer.setSVI(temp_bool);
        ResetB
        goto menu_input;
        break;
      case DeviceUpdateChoices::CONT:
        Switch::updateSwitch(buffer, i);
        std::cout << "File Successfully Updated" << std::endl;
        break;
      default:
        std::cerr << "ERR: Input a valid value" << std::endl;
        goto menu_input;
        break;
    }
  } catch (std::string ex) {
    std::cerr << "ERR: " << ex << std::endl;
    main();
  }
}
