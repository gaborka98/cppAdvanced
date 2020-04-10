//
//  Film.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 06..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include "Film.hpp"


Film::Film(std::string title, std::string originalTitle, std::string category, double score, int watched, int playTime, std::string audio, std::string subtitle, int likes, int disLikes) : Node(title, originalTitle, category, score, watched, playTime, audio, subtitle, likes, disLikes) {}

Film::~Film() {}
