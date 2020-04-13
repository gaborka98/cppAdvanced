//
//  menuSystem.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 12..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include "menuSystem.hpp"

void filmDetailsMenu(Node* selectedMovie, MysqlConnector* mysql, User* loggedInUser) {
    int input;
    std::cout << "_________________________________________________" << std::endl;
    std::cout << "Kivalsztott film: " << selectedMovie->getTitle() << std::endl;
    std::cout << "Mit szeretnel tenni a kivalasztott filmel?" << std::endl;
    std::cout << "1, pontozni" << std::endl;
    std::cout << "2, latottnak jelolni" << std::endl;
    std::cout << "3, torolni az adatbazisbol" << std::endl;
    std::cout << "4, adatok megtekintese" << std::endl;
    std::cout << "0, visszalepes" << std::endl;
    std::cout << "valasztas: ";
    std::cin >> input;
    
    if (input == 0) {
        return;
    } else if (input == 1) {
        int localScore;
        do{
            std::cout << "_________________________________________________" << std::endl;
            std::cout << "Kerlek add meg a pontszamot 0-10-es skalan. (visszalepes - 0)" << std::endl;
            std::cout<< "pontszam: ";
            std::cin >> localScore;
            if (localScore == 0) { return; }
            if (localScore < 0 || localScore > 10) {
                std::cout << "~~~~~~~~~~ HIBA ~~~~~~~~~~" << std::endl;
                std::cout << "hibas pontszamot adtal meg, csak 0-10 kozotti pontszam adhato!" << std::endl;
            }
        } while (localScore < 0 || localScore > 10);
        
        std::cout<< selectedMovie->getId() << std::endl;
        mysql->insertEvent(4, selectedMovie->getId(), loggedInUser->getId(), localScore);
        mysql->updateScore(selectedMovie->getId());
        
    // TODO: ezeket megcsinalni
    } else if (input == 1) {
        
    } else if (input == 2) {
        
    } else if (input == 3) {
        
    } else if (input == 4) {
        
    }
}

void keresesMenu(MovieSystem* database, MysqlConnector* mysql, User* loggedInUser) {
    std::string input;
    std::cout << "Ird be a keresett film cimet vagy annak reszletet (visszalepes - 0)" << std::endl;
    std::cout << "Kereses: ";
    std::cin >> input;
    
    if (input == "0") { return; }
    
    int sorsz = 1;
    
    std::vector<Node*> result = database->searchInLocalDatabase(input);
    
    for (auto &iter :result) {
        std::cout << sorsz << ". ";
        iter->print();
        sorsz++;
    }
    int selectedFilm;
    std::cout << "Valassz a listabol a sorszam alapjan filmet (visszalepes - 0)" << std::endl;
    std::cout << "valasztas: ";
    std::cin >> selectedFilm;
    if (selectedFilm == 0) { return; }
    filmDetailsMenu(result[selectedFilm - 1], mysql, loggedInUser);
    database->refreshDatabaseFromSql();
}

void printMenu(MovieSystem* database, MysqlConnector* mysql, User* loggedInUser) {
    int input;
    do {
        std::cout << "______________________________________" << std::endl;
        std::cout << "Valassz a menubol a sorszam beirasaval" << std::endl;
        std::cout << "1, Film keresese" << std::endl;
        std::cout << "2, Film hozzaadasa" << std::endl;
        std::cout << "3, Jo napom van" << std::endl;
        std::cout << "0, Kilepes" << std::endl;
        std::cin >> input;
        
        if (input == 0) { break; }
        
        else if (input == 1) {
            keresesMenu(database, mysql, loggedInUser);
        }
        
    } while (input != 0);

}
