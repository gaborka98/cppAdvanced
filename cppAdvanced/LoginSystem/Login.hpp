//
//  Login.hpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 12..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#ifndef Login_hpp
#define Login_hpp

#include <stdio.h>
#include <string>

#include "User.hpp"
#include "../mysqlConnector.hpp"

User* loginProcess(MysqlConnector* mysql);

#endif /* Login_hpp */
