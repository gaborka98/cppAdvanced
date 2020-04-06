//
//  User.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 06..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include "User.hpp"


User::User(std::string name, std::string email, std::string password, std::list<Film *> films) : name(name), email(email), password(password), watched(films) {}

User::~User() {
    for (auto &&d : watched) {
        delete d;
    }
    watched.clear();
}



