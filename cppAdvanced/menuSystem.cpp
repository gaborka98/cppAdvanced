//
//  menuSystem.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 12..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include <iostream>
#include <string>

void keresesMenu() {
    std::string input;
    std::cout << "Ird be a keresett film cimet vagy annak reszletet" << std::endl;
    std::cout << "Kereses: ";
    std::cin >> input;
//    for (auto &iter : database->searchInLocalDatabase(input)) {
//        iter->print();
//    }
    
}

void printMenu() {
    int input;
    do {
        std::cout << "Valassz a menubol a sorszam beirasaval" << std::endl;
        std::cout << "1, Film keresese" << std::endl;
        std::cout << "2, Film hozzaadasa" << std::endl;
        std::cout << "3, Jo napom van" << std::endl;
        std::cout << "0, Kilepes" << std::endl;
        std::cin >> input;
        
        if (input == 0) { break; }
        
        else if (input == 1) {
            keresesMenu();
        }
        
    } while (input != 0);

}
