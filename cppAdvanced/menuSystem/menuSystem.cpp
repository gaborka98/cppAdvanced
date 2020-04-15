//
//  menuSystem.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 12..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include "menuSystem.hpp"

void filmDetailsMenu(Node* selectedMovie, MysqlConnector* mysql, User* loggedInUser, MovieSystem* database) {
    int input;
    std::cout << "_________________________________________________" << std::endl;
    std::cout << "Kivalsztott film: " << selectedMovie->getTitle() << std::endl;
    std::cout << "Mit szeretnel tenni a kivalasztott filmel?" << std::endl;
    std::cout << "1, pontozni" << std::endl;
    std::cout << "2, latottnak jelolni" << std::endl;
    std::cout << "3, torolni az adatbazisbol" << std::endl;
    std::cout << "4, adatok megtekintese" << std::endl;
    std::cout << "5, like" << std::endl;
    std::cout << "6, dislike" << std::endl;
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
        selectedMovie->setScore((selectedMovie->getScore() + localScore) / selectedMovie->getScoreCount());
        
    } else if (input == 2) {
        char tmp;
        std::cout << "_________________________________________________" << std::endl;
        std::cout << "Biztos latottnak jelolod a(z) " << selectedMovie->getTitle() << " cimu filmet? i/n" << std::endl;
        do {
            std::cin >> tmp;
            if (tmp == 'n') { return; }
            else if (tmp == 'i') break;
            else std::cout << "Csak 'i' es 'n' betuket adhatsz meg kis betukkel!!!"<< std::endl;
        } while (tmp != 'n' || tmp != 'i');
        
        mysql->insertEvent(3, selectedMovie->getId(), loggedInUser->getId());
        loggedInUser->addWatched(selectedMovie);
        
    } else if (input == 3) {
        char tmp;
        std::cout << "_________________________________________________" << std::endl;
        std::cout << "Biztosan torolni akarod a(z)" << selectedMovie->getTitle() << " cimu filmet az adatbazisbol? i/n" << std::endl;
        std::cin >> tmp;
        do {
            std::cin >> tmp;
            if (tmp == 'n') { return; }
            else if (tmp == 'i') break;
            else std::cout << "Csak 'i' es 'n' betuket adhatsz meg kis betukkel!!!"<< std::endl;
        } while (tmp != 'n' || tmp != 'i');
        
        mysql->deleteFromDatabase(selectedMovie->getId());
        database->deleteFromLocalDatabase(selectedMovie);
        
    } else if (input == 4) {
        selectedMovie->printDetails();
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
    filmDetailsMenu(result[selectedFilm - 1], mysql, loggedInUser, database);
    database->refreshDatabaseFromSql();
}

void printMenu(MovieSystem* database, MysqlConnector* mysql, User* loggedInUser) {
    int input;
    do {
        std::cout << "______________________________________" << std::endl;
        std::cout << "Valassz a menubol a sorszam beirasaval" << std::endl;
        std::cout << "1, Film keresese" << std::endl;
        std::cout << "2, Film hozzaadasa" << std::endl;
        std::cout << "3, Sorozat hozzaadasa" << std::endl;
        std::cout << "4, Jo napom van" << std::endl;
        std::cout << "0, Kilepes" << std::endl;
        std::cin >> input;
        
        if (input == 0) { break; }
        
        else if (input == 1) {
            keresesMenu(database, mysql, loggedInUser);
        } else if (input == 2) {
            std::string title, originalTitle, category, audio, subtitle;
            int playtime;
            
            std::cout << "______________________________________" << std::endl;
            std::cout << "Ird be a film magyar cimet:" << std::endl;
            std::cin >> title;
            std::cout << "Ird be a film eredeti cimet:" << std::endl;
            std::cin >> originalTitle;
            std::cout << "Ird be a film kategoriajat:" << std::endl;
            std::cin >> category;
            std::cout << "Ird be a film hosszad:" << std::endl;
            std::cin >> playtime;
            std::cout << "Ird be a film audio nyelvet:" << std::endl;
            std::cin >> audio;
            std::cout << "Ird be a film feliratanak nyelvet:" << std::endl;
            std::cin >> subtitle;
            
            int id = mysql->addToDatabase(title, originalTitle, category, playtime, audio, subtitle);
            database->addFilm(id, title, originalTitle, category, 0., 0, playtime, audio, subtitle, 0, 0);
            
        } else if (input == 3) {
            std::string title, originalTitle, category, audio, subtitle;
            int playtime = 0, season = 0, episodes = 0;
            std::cout << "______________________________________" << std::endl;
            std::cout << "Ird be a sorozat magyar cimet:" << std::endl;
            std::cin >> title;
            std::cout << "Ird be a sorozat eredeti cimet:" << std::endl;
            std::cin >> originalTitle;
            std::cout << "Ird be a sorozat kategoriajat:" << std::endl;
            std::cin >> category;
            std::cout << "Ird be a sorozat hosszad:" << std::endl;
            std::cin >> playtime;
            std::cout << "Ird be a sorozat audio nyelvet:" << std::endl;
            std::cin >> audio;
            std::cout << "Ird be a sorozat feliratanak nyelvet:" << std::endl;
            std::cin >> subtitle;
            std::cout << "Ird be a sorozat evadanak szamat:" << std::endl;
            std::cin >> season;
            std::cout << "Ird be a sorozat episodjainak szamat evadonkent:" << std::endl;
            std::cin >> episodes;
            
            std::map<int, std::list<Film*>> seasons;
            std::list<Film*> episodesInSeasons;
            
            int lastid = mysql->getLastId();
            
            for (unsigned i = 0; i < season; i++) {
                for (unsigned j = 0; j < episodes; j++) {
                    mysql->addToDatabase(title + "S" + std::to_string(i) + "E" + std::to_string(j), originalTitle, category, playtime, audio, subtitle);
                    episodesInSeasons.push_back(new Film(++lastid, title + "S" + std::to_string(i) + "E" + std::to_string(j) ,originalTitle,category,0,0,playtime,audio,subtitle,0,0));
                }
                seasons.insert(std::make_pair(i, episodesInSeasons));
            }
            
            database->addSeries(++lastid,title, originalTitle, category,0,0, playtime, audio,subtitle, 0, 0, seasons);
        } else if (input == 4) {
            
        }
        
    } while (input != 0);

}
