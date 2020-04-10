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

#include "Node.hpp"
#include "Film.hpp"

class Series : public Node {
    std::map<int, std::list<Film*>> seasons;
    
public:
    Series(std::string title, std::string originalTitle, std::string category, double score, int watched, int playTime, std::string audio, std::string subtitle, int likes, int dislikes, std::map<int, std::list<Film*>> seasons);
    ~Series();
    
    std::map<int, std::list<Film*>> getSeasons();
};

#endif /* Series_hpp */
