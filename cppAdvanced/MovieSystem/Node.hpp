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
protected:
    int id;
    std::string title;
    std::string originalTitle;
    std::string category;
    double score;
    int scoreCount = 0;
    int watched;
    int playTime;
    std::string audio;
    std::string subtitle;
    int likes;
    int disLikes;
    
public:
    Node( int id, std::string title, std::string originalTitle, std::string category, double score, int watched, int playTime, std::string audio, std::string subtitle, int likes, int disLikes);
    virtual ~Node() = 0;
    
    void setScore(double pScore);
    
    int getScoreCount();
    double getScore();
    std::string getTitle();
    int getId();
    std::string getOriginalTitle();
    
    virtual void print();
    virtual void printDetails();
};

#endif /* Node_hpp */
