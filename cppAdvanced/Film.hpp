//
//  Film.hpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 06..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#ifndef Film_hpp
#define Film_hpp

#include <stdio.h>
#include <string>
#include <list>

class Film {
    std::string title;
    std::string category;
public:
    Film(std::string title, std::string category);
    ~Film();
};

#endif /* Film_hpp */
