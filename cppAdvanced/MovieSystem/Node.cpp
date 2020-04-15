//
//  Node.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 10..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include "Node.hpp"

Node::Node(int id, std::string title, std::string originalTitle, std::string category, double score, int watched, int playTime, std::string audio, std::string subtitle, int likes, int disLikes) : id(id), title(title), originalTitle(originalTitle), category(category), score(score), watched(watched), playTime(playTime), audio(audio), subtitle(subtitle), likes(likes), disLikes(disLikes) {}

Node::~Node() {}

void Node::setScore(double pScore){
    score = pScore;
}

double Node::getScore() {
    return score;
}

int Node::getScoreCount() {
    return ++scoreCount;
}

std::string Node::getTitle() {
    return title;
}

int Node::getId() { return id; }

std::string Node::getOriginalTitle() { return originalTitle; }

void Node::print() {
    std::cout<< title << std::endl;
}

void Node::printDetails() {
    std::cout << "Cim: " << title << std::endl;
    std::cout << "Eredeti cime: " << originalTitle << std::endl;
    std::cout << "Kategoria: " << category << std::endl;
    std::cout << "Hossza: " << playTime << " perc" << std::endl;
    std::cout << "Audio: " << audio << std::endl;
    std::cout << "Felirat: " << subtitle << std::endl;
    std::cout << "Pontszam: " << score << std::endl;
    std::cout << "Like: " << likes << std::endl;
    std::cout << "Dislikes: " << disLikes << std::endl;
}
