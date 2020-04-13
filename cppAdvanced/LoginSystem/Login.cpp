//
//  Login.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 12..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include "Login.hpp"

User* loginProcess(MysqlConnector* mysql) {
    std::string username, password;
    
    std::cout << "Film es sorozat nyilvantarto rendszer" << std::endl;
    std::cout << "Bejelentkezes" << std::endl;
    
    do {
        std::cout << "Felsznalonev: ";
        std::cin >> username;
        std::cout << "Jelszo: ";
        std::cin >> password;
        
        if (password == mysql->getUserPass(username)) {
            std::cout << "\nSikeres bejelentkezes!\n"<< std::endl;
        } else { std::cout<< "\nSikertelen bejelentkezes...\n" << std::endl; }
    } while (password != mysql->getUserPass(username));

    
    return mysql->loadUserData(username);
}
