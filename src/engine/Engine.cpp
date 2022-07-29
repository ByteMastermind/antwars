//
// Created by michal on 25.5.22.
//

#include "Engine.h"

Engine::Engine() : m_mouse(-1, -1), m_AIDifficulty(100) {
    m_numberOfBlocks = screenConstants::SCREEN_WIDTH / screenConstants::BLOCK_SIZE;
}

void Engine::loadMap(const std::string & filePath) {
    MapFile map(filePath);
    map.processFile();
    m_characters = map.getPlaces();
    m_AIDifficulty = map.getAIdifficulty();
    std::cout << "AI difficulty set to: " << m_AIDifficulty << std::endl;
    fillMap();
    findShortestPaths();
}

void Engine::loadGameSave(const std::string & filePath) {
    SaveFile file(filePath);
    file.processFile();
    m_characters = file.getPlaces();
    m_AIDifficulty = file.getAIdifficulty();
    std::cout << "AI difficulty set to: " << m_AIDifficulty << std::endl;
    fillMap();
    findShortestPaths();
}

void Engine::initCharacters() {
    for (auto & character : m_characters)
        character->initCharacter(m_window.getRenderer());
}

void Engine::run() {
    if ( TTF_Init() < 0 )
        throw std::runtime_error("Error initializing SDL_ttf");

    size_t counter = 0;
    m_isRunning = true;
    while (m_isRunning) {
        SDL_Delay(screenConstants::DELAY);
        end();
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        m_mouse = MatrixCoordinates(mouseY / screenConstants::BLOCK_SIZE, mouseX / screenConstants::BLOCK_SIZE);
        if (counter % m_AIDifficulty == 0)
            chooseTarget();
        catchEvent();
        m_window.updateBackground();
        for (auto & character : m_characters) {
            character->progress(m_mouse);
        }
        for (auto & character : m_characters) {
            if (character->getType() == "eanthill")
                break;
            killAnts(character);
        }
        m_window.updateRenderer();
        counter++;
    }

    TTF_Quit();
}

void Engine::catchEvent() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {

            case SDL_QUIT:  // Quiting
                m_isRunning = false;
                break;

            case SDL_KEYDOWN:   // Saving
                if (event.key.keysym.sym == SDLK_s) {
                    saveGame();
                    m_isRunning = false;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:   // Selecting
                std::cout << m_mouse.row << " " << m_mouse.col << std::endl;
                if (!m_isSelected) {
                    if (selectAnthill()) {
                        m_isSelected = true;
                        std::cout << "Selected Friendly" << std::endl;
                        m_selectedCharacter = getTargetPointer();
                    }
                }
                else if (m_isSelected) {
                    if ((unsigned) m_mouse.col == m_selectedCharacter->getX() / screenConstants::BLOCK_SIZE &&
                        (unsigned) m_mouse.row == m_selectedCharacter->getY() / screenConstants::BLOCK_SIZE) {

                        m_isSelected = false;
                        m_selectedCharacter->setTarget(nullptr, nullptr);
                    }
                    else if (selectTarget()) {
                        m_isSelected = false;
                        std::cout << "Selected Target" << std::endl;
                    }
                }
                break;
        }
    }
}

bool Engine::selectAnthill() const {
    for (auto & character : m_characters) {
        if (character->getX() / 100 == m_mouse.col && character->getY() / 100 == m_mouse.row) {
            if (character->setSelected(!character->isSelected()))
                return true;
            return false;
        }
    }
    return false;
}

bool Engine::isTarget() const {
    for (auto & character : m_characters) {
        if (character->getX() / 100 == m_mouse.col && character->getY() / 100 == m_mouse.row) {
            if (character->getType() != "obstacle")
                return true;
            return false;
        }
    }
    return false;
}

std::shared_ptr<Character> Engine::getTargetPointer() const {
    for (auto & character : m_characters) {
        if (character->getX() / 100 == m_mouse.col && character->getY() / 100 == m_mouse.row) {
            if (character->getType() != "obstacle")
                return character;
            return nullptr;
        }
    }
    return nullptr;
}

bool Engine::selectTarget() const {
    if (!isTarget())
        return false;
    std::shared_ptr<Character> target = getTargetPointer();
    if (target->getAntCount() == 0)
        return false;
    if (m_selectedCharacter->setTarget(target, getPathPointer(m_selectedCharacter, target)))
        return true;
    return false;
}

void Engine::findShortestPaths() {
    for (size_t i = 0; i < m_characters.size() - 1; i++) {
        if (m_characters[i]->getType() == "obstacle")
            continue;
        MatrixCoordinates start(m_characters[i]->getY() / screenConstants::BLOCK_SIZE, m_characters[i]->getX() / screenConstants::BLOCK_SIZE);
        for (size_t j = i + 1; j < m_characters.size(); j++) {
            if (m_characters[j]->getType() == "obstacle")
                continue;
            MatrixCoordinates end(m_characters[j]->getY() / screenConstants::BLOCK_SIZE, m_characters[j]->getX() / screenConstants::BLOCK_SIZE);
            findShortestPath(start, end);
        }
    }
    std::cout << "Found shortest paths" << std::endl;
}

void Engine::fillMap() {
    for (size_t i = 0; i < m_numberOfBlocks; i++) {
        m_map.push_back(std::vector<bool>());
        for (size_t j = 0; j < m_numberOfBlocks; j++) {
            m_map[i].push_back(false);
        }
    }

    for (auto & character : m_characters) {
        m_map[character->getY() / screenConstants::BLOCK_SIZE][character->getX() / screenConstants::BLOCK_SIZE] = true;
    }
}

void Engine::findShortestPath(const MatrixCoordinates & start, const MatrixCoordinates & end) {
    Map<Node> map;
    for (size_t i = 0; i < m_numberOfBlocks; i++) {
        map.emplace_back(std::vector<Node>());
        for (size_t j = 0; j < m_numberOfBlocks; j++)
            map[i].emplace_back(MatrixCoordinates(-1, -1));
    }
    std::queue<MatrixCoordinates> q;

    q.emplace(end);

    while (!q.empty()) {
        MatrixCoordinates front = q.front();
        map[front.row][front.col].visited = true;
        q.pop();

        if (front.row != 0 && (!m_map[front.row - 1][front.col] || MatrixCoordinates(front.row - 1, front.col) == start) && !map[front.row - 1][front.col].visited) {
            q.emplace(front.row - 1, front.col);
            map[front.row - 1][front.col].previous = front;
            if (MatrixCoordinates(front.row - 1, front.col) == start)
                break;
        }

        if (front.col < (int) m_numberOfBlocks - 1 && (!m_map[front.row][front.col + 1] || MatrixCoordinates(front.row, front.col + 1) == start) && !map[front.row][front.col + 1].visited) {
            q.emplace(front.row, front.col + 1);
            map[front.row][front.col + 1].previous = front;
            if (MatrixCoordinates(front.row, front.col + 1) == start)
                break;
        }

        if (front.row < (int) m_numberOfBlocks - 1 && (!m_map[front.row + 1][front.col] || MatrixCoordinates(front.row + 1, front.col) == start) && !map[front.row + 1][front.col].visited) {
            q.emplace(front.row + 1, front.col);
            map[front.row + 1][front.col].previous = front;
            if (MatrixCoordinates(front.row + 1, front.col) == start)
                break;
        }

        if (front.col != 0 && (!m_map[front.row][front.col - 1] || MatrixCoordinates(front.row, front.col - 1) == start) && !map[front.row][front.col - 1].visited) {
            q.emplace(front.row, front.col - 1);
            map[front.row][front.col - 1].previous = front;
            if (MatrixCoordinates(front.row, front.col - 1) == start)
                break;
        }
    }

    if (map[start.row][start.col].previous.col == -1)
        throw std::runtime_error("There is no path between some two anthills");

    Path path;
    MatrixCoordinates tmp = start;
    while (tmp != end) {
        path.push_back(tmp);
        tmp = map[tmp.row][tmp.col].previous;
    }
    path.push_back(tmp);    // Even end MatrixCoordinates
    m_shortestPaths.push_back(path);
}

std::shared_ptr<Path> Engine::getPathPointer(const std::shared_ptr<Character> source, const std::shared_ptr<Character> target) const {
    for (auto & path : m_shortestPaths) {
        if (((unsigned) path[0].row == (source->getY() / screenConstants::BLOCK_SIZE) &&
            (unsigned) path[0].col == (source->getX() / screenConstants::BLOCK_SIZE) &&
            (unsigned) path[path.size() - 1].row == (target->getY() / screenConstants::BLOCK_SIZE) &&
            (unsigned) path[path.size() - 1].col == (target->getX() / screenConstants::BLOCK_SIZE)) ||
            ((unsigned) path[0].row == (target->getY() / screenConstants::BLOCK_SIZE) &&
            (unsigned) path[0].col == (target->getX() / screenConstants::BLOCK_SIZE) &&
            (unsigned) path[path.size() - 1].row == (source->getY() / screenConstants::BLOCK_SIZE) &&
            (unsigned) path[path.size() - 1].col == (source->getX() / screenConstants::BLOCK_SIZE)))

            return std::make_shared<Path>(path);
    }
    throw std::runtime_error("There is no path suitable for these two places");
}

void Engine::chooseTarget() const {
    // Finding anthill with the smallest amount of ants
    size_t smallestAntCount = 99999;
    std::shared_ptr<Character> smallest = nullptr;
    for (auto & character : m_characters) {
        if (character->getType() != "fanthill")
            break;
        if (character->getAntCount() < smallestAntCount && character->getAntCount() != 0) {
            smallest = character;
            smallestAntCount = character->getAntCount();
        }
    }

    // Assigning the target to every enemy anthill
    if (smallest == nullptr)
        return;
    for (auto & character : m_characters) {
        if (character->getType() == "obstacle")
            break;
        if (character->getType() == "eanthill")
            character->setTarget(smallest, getPathPointer(character, smallest));
    }
    std::cout << "Set targets to enemy anthills" << std::endl;
}

void Engine::end() {
    size_t fanthillAlive = 0;
    size_t eanthillAlive = 0;

    for (auto & character : m_characters) {
        if (character->getType() == "obstacle")
            break;
        if (character->getType() == "fanthill" && character->getAntCount() > 0)
            fanthillAlive++;
        if (character->getType() == "eanthill" && character->getAntCount() > 0)
            eanthillAlive++;
        if (fanthillAlive > 0 && eanthillAlive > 0)
            return;
    }
    m_isRunning = false;
    if (fanthillAlive > 0)
        std::cout << "You won!" << std::endl;
    else if (fanthillAlive == eanthillAlive)
        std::cout << "It's a draw!" << std::endl;
    else
        std::cout << "You lost!" << std::endl;
}

void Engine::killAnts(std::shared_ptr<Character> & character) {
    auto it = character->getAnts().begin();
    while (it != character->getAnts().end())
    {
        if (isAntNear((*it)->getX(), (*it)->getY(), character))
            it = character->getAnts().erase(it);
        else
            ++it;
    }
}

bool Engine::isAntNear(const int x, const int y, const std::shared_ptr<Character> ch) {
    for (auto & character : m_characters) {
        if (character->getType() != "eanthill")
            continue;
        if (character->getType() == "obstacle")
            return false;
        if (character == ch)
            continue;
        auto it = character->getAnts().begin();
        while (it != character->getAnts().end()) {
            if ((*it)->getX() / 100 == x / 100 && (*it)->getY() / 100 == y / 100) {
                character->getAnts().erase(it);
                return true;
            }
            else
                ++it;
        }
    }
    return false;
}

void Engine::saveGame() const {
    std::string output;

    auto character = m_characters.begin();
    size_t count = 0;
    output.append(std::to_string(m_AIDifficulty));
    output.append("\n");
    output.append("fa\n");
    while (character != m_characters.end() && (*character)->getType() == "fanthill") {
        output.append((*character)->printInfo());
        count++;
        character++;
    }
    if (!count)
        throw std::runtime_error("Cannot save at this game state.");

    count = 0;
    output.append("ea\n");
    while (character != m_characters.end() && (*character)->getType() == "eanthill") {
        output.append((*character)->printInfo());
        count++;
        character++;
    }
    if (!count)
        throw std::runtime_error("Cannot save at this game state.");

    output.append("o\n");
    while (character != m_characters.end()) {
        output.append((*character)->printInfo());
        count++;
        character++;
    }

    std::ofstream f("examples/game_save");
    if (!f.is_open())
        throw std::runtime_error("Game could not be saved");

    f << output << "\n";
    if (f.bad())
        throw std::runtime_error("Could not write to file");

    f.close();
}
