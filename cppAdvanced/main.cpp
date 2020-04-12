//
//  main.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 03. 31..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include <iostream>
#include "MovieSystem.hpp"
#include "mysqlConnector.hpp"


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

void keresesMenu(MovieSystem* database) {
    std::string input;
    std::cout << "Ird be a keresett film cimet vagy annak reszletet" << std::endl;
    std::cout << "Kereses: ";
    std::cin >> input;
    for (auto &iter : database->searchInLocalDatabase(input)) {
        iter->print();
    }
    
}

void printMenu(MysqlConnector* mysql, MovieSystem* database, User* loggedInUser) {
    int input;
    do {
        std::cout << "Valassz a menubol a sorszam beirasaval" << std::endl;
        std::cout << "1, Film keresese" << std::endl;
        std::cout << "2, Film hozzaadasa" << std::endl;
        std::cout << "3, Jo napom van" << std::endl;
        std::cout << "0, Kilepes" << std::endl;
        
        std::cout << "valasztas: ";
        std::cin >> input;
        
        if (input == 0) { break; }
        
        else if (input == 1) {
            keresesMenu(database);
        }
        
    } while (input != 0);

}

int main(int argc, const char * argv[]) {
    MysqlConnector* mysql = new MysqlConnector("mysql://127.0.0.1:3306", "root", "Gaborka11", "cpp");
    MovieSystem* database = new MovieSystem(mysql);
    User* loggedInUser = loginProcess(mysql);
    
    database->loadEverythingFromSql();
//    database->printAllWhatIsLoad();
    
    printMenu(mysql, database, loggedInUser);
    
    
    return 0;
}
