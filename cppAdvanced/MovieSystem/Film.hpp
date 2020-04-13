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

#include "Node.hpp"

class Film : public Node {

public:
    Film(int id, std::string title, std::string originalTitle, std::string category, double score, int watched, int playTime, std::string audio, std::string subtitle, int likes, int disLikes);
    ~Film();
    
};

#endif /* Film_hpp */
