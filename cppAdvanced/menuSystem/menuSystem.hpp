//
//  menuSystem.hpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 12..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#ifndef menuSystem_hpp
#define menuSystem_hpp

#include <stdio.h>
#include <string>
#include <iostream>

#include "MovieSystem.hpp"
#include "mysqlConnector.hpp"

void printMenu(MovieSystem* database, MysqlConnector* mysql, User* loggedInUser);
void keresesMenu(MovieSystem* database, MysqlConnector* mysql, User* loggedInUser);
void filmDetailsMenu(Node* selectedMovie, MysqlConnector* mysql, User* loggedInUser);

#endif /* menuSystem_hpp */
