//
//  User.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 06..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include "User.hpp"


User::User(int id, std::string name, std::string username,  std::string email, std::string password) : id(id), name(name), username(username), email(email), password(password) {}

User::~User() {
}

void User::addWatched(Node* movie) {
    watched.push_back(movie);
}

bool User::notContainsWatched(Node* movie) {
    for (auto &iter : watched) {
        if (iter == movie) {
            return false;
        }
    }
    return true;
}

int User::getId() { return id; }

