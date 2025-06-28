#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <exception>
#include "Bowling.h"

// Constructor
BowlingGame::BowlingGame() {
    rolls = std::make_unique<std::vector<int>>();
    std::cout << "BowlingGame: BowlingGame Constructor called" << std::endl;
}

// Destructor
BowlingGame::~BowlingGame() {
    std::cout << "BowlingGame: BowlingGame Destructor called" << std::endl;
    std::cout << "BowlingGame: BowlingGame object Destroyed" << std::endl;
}

void BowlingGame::roll(int pins) {
    rolls->push_back(pins);
}

bool BowlingGame::isStrike(int rollIndex) const {
    return rollIndex < rolls->size() && (*rolls)[rollIndex] == 10;
}

bool BowlingGame::isSpare(int rollIndex) const {
    return rollIndex + 1 < rolls->size() && 
           (*rolls)[rollIndex] + (*rolls)[rollIndex + 1] == 10;
}

int BowlingGame::Score() {
    int totalScore = 0;
    int rollIndex = 0;

    for (int frame = 0; frame < 10; ++frame) {
        if (frame < 9) { // Frames 1-9
            if (rollIndex >= rolls->size()) break;  // Failure condition
            
            if (isStrike(rollIndex)) {
                // Strike: 10 + next two rolls
                totalScore += 10 + (*rolls)[rollIndex + 1] + (*rolls)[rollIndex + 2];
                rollIndex += 1;
            } else if (isSpare(rollIndex)) {
                // Spare: 10 + next roll
                totalScore += 10 + (*rolls)[rollIndex + 2];
                rollIndex += 2;
            } else {
                // Normal frame
                totalScore += (*rolls)[rollIndex] + (*rolls)[rollIndex + 1];
                rollIndex += 2;
            }
        } else { // 10th frame
            if (rollIndex >= rolls->size()) break; // failure conditionn
            
            if (isStrike(rollIndex) && isStrike(rollIndex + 1)) {
                // Two strikes in a row, in 10th frame
                totalScore += 20;
            }
            else{ // count all the remaining rolls
                totalScore += (*rolls)[rollIndex] + (*rolls)[rollIndex + 1] + (*rolls)[rollIndex + 2];
            }
            break; // End after 10th frame
        }
    }
    return totalScore;
}

void BowlingGame::DisplayScore() const {
    std::cout << "BowlingGame: Rolls: ";
    for (size_t i = 0; i < rolls->size(); ++i) {
        std::cout << (*rolls)[i];
        if (i < rolls->size() - 1) std::cout << " ";
    }
    std::cout << std::endl;
    std::cout << "BowlingGame: 🎉 Congratulations! You've Completed the game! 🎉" << std::endl;
    std::cout << "BowlingGame: ✨ Now let's see how you scored... ✨" << std::endl;
    std::cout << "BowlingGame: Total Score: " << const_cast<BowlingGame*>(this)->Score() << std::endl;
    std::cout << "BowlingGame: ***********GAME END***********" << std::endl;
}

void BowlingGame::Initiallize() {
    std::cout << "BowlingGame: Initiallize Started" << std::endl;
    
    std::string filename = "master";
    // Read rolls from file
    auto fileRolls = readRollsFromFile(filename);
    
    if (fileRolls->empty()) {
        std::cout << "BowlingGame: No rolls found in file!" << std::endl;
        return;
    }
    else{
        std::cout << "BowlingGame: **********GAME START**********" << std::endl;
        std::cout << "BowlingGame: Loading rolls from " << filename << " file..." << std::endl;
        
        // Add rolls to THIS object
        for (int roll : *fileRolls) {
            this->roll(roll);  // Saving values to Vector
        }
        
        std::cout << "BowlingGame: Loaded " << fileRolls->size() << " rolls successfully." << std::endl;
        // Calling the DisplayScore function
        DisplayScore();
    }
}

std::unique_ptr<std::vector<int>> BowlingGame::readRollsFromFile(const std::string& filename) {
    
    auto rolls = std::make_unique<std::vector<int>>();
    try{
        std::ifstream file(filename);
        
        if (!file.is_open()) {
            std::cout << "BowlingGame: Error: Cannot open file " << filename << std::endl;
            std::cout << "BowlingGame: Game cannot continue without data file!" << std::endl;
            throw std::runtime_error("Required data file not found: " + filename);
        }
        else{
            std::cout << "BowlingGame: " << filename << " File opened successfully." << std::endl;

            std::string line;
            if (std::getline(file, line)) {
                std::stringstream ss(line);
                int roll;
                
                while (ss >> roll) {
                    rolls->push_back(roll);
                    // Check if we've reached the maximum allowed rolls
                    if (rolls->size() >= 21) {
                        std::cout << "BowlingGame: Warning: Maximum 21 rolls allowed for 10 frames." << std::endl;
                        break;
                    }
                }
            }
            
            file.close();
        }
    }catch(const std::exception& exptObj){
        std::cerr << "BowlingGame: Caught Exception " << exptObj.what() << std::endl;
    }
    return rolls;
}