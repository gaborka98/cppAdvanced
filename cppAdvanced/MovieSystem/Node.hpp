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
#include <iostream>

class Node {
    int id;
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
    Node( int id, std::string title, std::string originalTitle, std::string category, double score, int watched, int playTime, std::string audio, std::string subtitle, int likes, int disLikes);
    virtual ~Node() = 0;
    
    std::string getTitle();
    int getId();
    std::string getOriginalTitle();
    
    virtual void print();
};

#endif /* Node_hpp */
