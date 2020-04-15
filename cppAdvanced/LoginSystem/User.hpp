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
#include <vector>

#include "Node.hpp"

class User {
    int id;
    std::string name;
    std::string username;
    std::string email;
    std::string password;
    std::vector<Node*> watched;
    
public:
    User(int id, std::string name, std::string username, std::string email, std::string password);
    ~User();
    
    void addWatched(Node* movie);
    
    int getId();
};

#endif /* User_hpp */
