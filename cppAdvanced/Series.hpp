//
//  Series.hpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 06..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#ifndef Series_hpp
#define Series_hpp

#include <stdio.h>
#include <string>
#include <map>
#include <list>

#include "Film.hpp"

class Series : public Film {
    std::map<int, std::list<Film*>> seasons;
//    std::list<Film*> episodes;
    
public:
    Series(std::string title, std::string category, std::map<int, std::list<Film*>> seasons);
    ~Series();
};

#endif /* Series_hpp */
