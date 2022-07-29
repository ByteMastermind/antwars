//
// Created by michal on 7.5.22.
//

#include "File.h"

File::File(std::string filePath) : m_filePath(std::move(filePath)) {

}

bool File::fileExist(const std::string &filePath) {
    if (FILE *file = fopen(filePath.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

std::string File::getFilePath() const {
    return m_filePath;
}

std::vector<std::shared_ptr<Character>> File::getPlaces() const {
    return m_places;
}

int File::getAIdifficulty() const {
    return m_AIdifficulty;
}
