#include "ActuationSystem.hpp"

#include <string>
#include <thread>
#include <iostream>
#include <sstream>
#include <chrono>
#include <vector>
#include <csignal>
#include <atomic>
#include <mutex>

const uint UPDATE_FREQ = 200;
const uint16_t ZERO_MOT_CMD = 1500;
const uint16_t NUM_MOTORS = 4, MIN_MOT_CMD = 1000, MAX_MOT_CMD = 2000;

std::vector<int> mot_cmds(NUM_MOTORS, ZERO_MOT_CMD);

std::atomic<bool> terminate;

std::mutex mut;

void signalHandler( int signum ) {
    terminate =true;
    std::this_thread::sleep_for(std::chrono::milliseconds(6));
    exit(signum);  
}
void thread_callback(const int num_mots);
int main(){

    std::string cmd;
    terminate = false;
    signal(SIGINT, signalHandler);  

    std::thread t1(thread_callback, NUM_MOTORS);
    while(true){
        uint16_t mot_num=0, mot_cmd=1000;
        std::getline(std::cin, cmd);

        std::istringstream iss(cmd);

        iss >> mot_num >> mot_cmd;
        if(mot_num < NUM_MOTORS && mot_cmd >= MIN_MOT_CMD && mot_cmd <= MAX_MOT_CMD){
            std::cout << "received command " << mot_cmd << " for motor number " << mot_num << std::endl; 
            mut.lock();
            mot_cmds[mot_num] = mot_cmd;
            mut.unlock();
        }


    }
    t1.join();

}

void thread_callback(const int num_mots){
    std::vector<HEAR::ESCMotor*> vec; 
    for(int i=0; i<num_mots; i++){
        auto mot = new HEAR::ESCMotor(i, UPDATE_FREQ);
        vec.push_back(mot);
    }
    while(!terminate){
        for(int i=0; i<num_mots; i++){
            mut.lock();
            vec[i]->applyCommand(mot_cmds[i]);
            mut.unlock();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/UPDATE_FREQ));
    }

    for(int i=0; i<num_mots; i++){
        vec[i]->applyCommand(ZERO_MOT_CMD);
    }
    std::cout << "Stopped all motors" << std::endl; 

}