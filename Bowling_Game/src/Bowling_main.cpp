#include <iostream>
#include <thread>
#include <chrono>
#include <exception>
#include "Bowling.h"

void RunThreadJoin(std::thread& thread){
    if (thread.joinable()){
        thread.join();
    }
}

void ThreadAct1(){  
    std::cout << "BowlingGame: ThreadAct1 Function Called" << std::endl;
    // Creating a BowlingGame object
    BowlingGame BowlingGame_obj;
    std::cout << "BowlingGame: BowlingGame object Created" << std::endl;
    // Calling the Initiallize function
    BowlingGame_obj.Initiallize();  
    
    std::this_thread::sleep_for(std::chrono::seconds(1));  // Sleep for 1 second
    
}

int main() {
    try{
        std::cout<< "BowlingGame: BowlingGame Main Function Called" << std::endl;
        // Creating a Thread
        std::thread act1(&ThreadAct1);
        ::RunThreadJoin(act1);
    }
    catch(const std::exception& exptobj){
        std::cerr << "BowlingGame: Application Caught Exception >>>" << exptobj.what() << std::endl;
    }
    catch(...){
        std::cerr << "BowlingGame: Application Generic Exception is caught" << std::endl;
    }
    return 0;
}
