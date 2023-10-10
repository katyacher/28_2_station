#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

std::mutex station_lock;
std::mutex stdout_accses;

class Train {
    std::string name = "";
    int travel_time;
public:
    Train(std::string n, int s): name{n}, travel_time{s}{};
    ~Train(){};

    int getTravel_time(){
        return travel_time;
    };

    void arrival(){
        std::cout << "Arrival of train " << name << std::endl;
    };

    void wait(){
        std::cout << "\nThe train " << name << " is waiting to arrive." << std::endl;
    };

    void wait_depart(){
        std::cout << "The train " << name << " is waiting to depart( type \"depart\"): ";
    };

    void depart(){
        std::cout << "Departure of train  " << name << std::endl;
    };


};

void station(Train* t){
    std::this_thread::sleep_for(std::chrono::seconds(t->getTravel_time()));

    if(station_lock.try_lock()){
        station_lock.unlock();
    } else {
        t->wait();
    }

    station_lock.lock();

    stdout_accses.lock();
    t->arrival();
    stdout_accses.unlock();
    
    std::string command;
    do{
        t->wait_depart();
        std::cin >> command;
    }while(command != "depart");

    t->depart();
   
    station_lock.unlock();   
}

int main(int, char**){
    std::cout << "Hello, from 28_2_station!\n";

    std::vector<Train*> trains(3);
    for(int i = 0; i < 3; ++i){
        std::cout << "Enter the name of the train: ";
        std::string name;
        std::cin >> name;
        std::cout << "Enter travel time: ";
        int time;
        std::cin >> time;
        while(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Enter travel time: ";
            std::cin.clear();
            std::cin.ignore();
            std::cin >> time;
        }
           
        Train* train = new Train(name, time);
        trains[i] = train;
    }

    std::vector<std::thread> trainThreads(3);

    for(int i = 0; i < trainThreads.size(); ++i)
        trainThreads[i] = std::thread(station, std::ref(trains[i]));

    for(int i = 0; i < trainThreads.size(); ++i)
        trainThreads[i].join();

    return 0;
}
