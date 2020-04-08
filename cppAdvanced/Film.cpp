//
//  Film.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 06..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include "Film.hpp"


Film::Film(std::string title, std::string originalTitle, std::string category, double score, int watched, int playTime, std::string audio, std::string subtitle, int likes, int disLikes) : title(title), originalTitle(originalTitle), category(category), score(score), watched(watched), playTime(playTime), audio(audio), subtitle(subtitle), likes(likes), disLikes(disLikes) {}

Film::~Film() {}

