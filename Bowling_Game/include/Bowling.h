#ifndef BOWLINGGAME_H
#define BOWLINGGAME_H

#include <vector>
#include <memory>

class BowlingGame {
public:
    explicit BowlingGame();  // Constructor
    virtual ~BowlingGame(); // Destructor

    void Initiallize();
    std::unique_ptr<std::vector<int>> readRollsFromFile(const std::string& filename);
    void roll(int pins);
    int Score();
    void DisplayScore() const;

private:
    std::unique_ptr<std::vector<int>> rolls;
    bool isStrike(int rollIndex) const;
    bool isSpare(int rollIndex) const;
};

#endif
