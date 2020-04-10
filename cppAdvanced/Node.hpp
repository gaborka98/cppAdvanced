//
//  Node.hpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 10..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <string>

class Node {
    std::string title;
    std::string originalTitle;
    std::string category;
    double score;
    int watched;
    int playTime;
    std::string audio;
    std::string subtitle;
    int likes;
    int disLikes;
    
public:
    Node(std::string title, std::string originalTitle, std::string category, double score, int watched, int playTime, std::string audio, std::string subtitle, int likes, int disLikes);
    virtual ~Node() = 0;
    
    std::string getTitle();
};

#endif /* Node_hpp */
