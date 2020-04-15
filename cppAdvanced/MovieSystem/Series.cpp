//
//  Series.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 06..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include "Series.hpp"


Series::Series(int id, std::string title, std::string originalTitle, std::string category, double score, int watched, int playtime, std::string audio, std::string subtitle, int likes, int dislikes, std::map<int, std::list<Film*>> seasons) : Node(id, title, originalTitle, category, score, watched, playtime, audio, subtitle, likes, dislikes), seasons(seasons) {}



Series::~Series() {
    for (auto &&d : seasons) {
        for (auto &&e : d.second) {
            delete e;
        }
        d.second.clear();
    }
    seasons.clear();
}

std::map<int, std::list<Film*>> Series::getSeasons() { return seasons; }

void Series::print() {
    std::cout << originalTitle << std::endl;
    for (auto &iter : seasons) {
        std::cout << "\t" << iter.first << ". evad" << std::endl;
        for (auto &d : iter.second) {
            std::cout << "\t\t" << d->getTitle() << std::endl;
        }
    }
}

void Series::printDetails() {
    std::cout << "Cim: " << originalTitle << std::endl;
    std::cout << "Evadok szama: " << seasons.size();
    std::cout << "Kategoria: " << category << std::endl;
    std::cout << "Hossza: " << playTime << " perc" << std::endl;
    std::cout << "Audio: " << audio << std::endl;
    std::cout << "Felirat: " << subtitle << std::endl;
    std::cout << "Pontszam: " << score << std::endl;
    std::cout << "Like: " << likes << std::endl;
    std::cout << "Dislikes: " << disLikes << std::endl;
}
