//
//  User.hpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 06..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#ifndef User_hpp
#define User_hpp

#include <stdio.h>
#include <string>
#include <list>

#include "Film.hpp"

class User {
    std::string name;
    std::string email;
    std::string password;
    std::list<Film*> watched;
    
public:
    User(std::string name, std::string email, std::string password, std::list<Film*> films);
    ~User();
};

#endif /* User_hpp */
