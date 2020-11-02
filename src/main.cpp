#include <iostream>
#include "Simulator.h";
#include <sstream>

/**
 * The main program for Simulation
 *
 * @author Akhil Pawar @ RIT CS
 */
int main() {
    /** Simulator */
    Simulator simulator{};

    /** input choice*/
    string choice;

    /** input command*/
    string command;

    cout<<"Enter command:"<<endl;
    getline(std::cin,command);

    std::istringstream iss(command);
    (iss >> choice);
    while (choice != "stop"){
        if(choice == "create"){
            std::istringstream iss(command);
            string temp;
            iss>>temp;
            string category;
            (iss >> category);
            string identity;
            (iss >> identity);
            string speed_s;
            (iss >> speed_s);
            double speed;
            speed = atof(speed_s.c_str());
            simulator.add_track(category, identity, speed);
        }else if(choice == "update"){
            std::istringstream iss(command);
            string temp;
            iss>>temp;
            string id;
            (iss >> id);
            string category;
            (iss >> category);
            string identity;
            (iss >> identity);
            string speed_s;
            (iss >> speed_s);
            double speed;
            speed = atof(speed_s.c_str());
            simulator.update_track(atoi(id.c_str()),category,identity,speed);
        }else if(choice == "delete"){
            std::istringstream iss(command);
            string temp;
            iss>>temp;
            string id;
            (iss >> id);
            simulator.delete_track(atoi(id.c_str()));
        }else if(choice == "correlate"){
            std::istringstream iss(command);
            string temp;
            iss>>temp;
            string id1;
            (iss >> id1);
            string id2;
            (iss >> id2);
            simulator.correlate_tracks(atoi(id1.c_str()),atoi(id2.c_str()));
        }else if(choice == "help"){
            cout<<"Welcome to the INS Kolkata Destroyer Simulator Guide"<<endl;
            cout<<"create: Create a track"<<endl;
            cout<<"\tusage: create {category} {identity} {speed}"<<endl;
            cout<<"update: Updates a track"<<endl;
            cout<<"\tusage: update {track_id} {category} {identity} {speed}"<<endl;
            cout<<"delete: Deletes a track"<<endl;
            cout<<"\tusage: delete {track_id}"<<endl;
            cout<<"correlate: Correlates two tracks"<<endl;
            cout<<"\tusage: correlate {track_1_id} {track_2_id}"<<endl;
            std::istringstream iss(command);
            string temp;
            iss>>temp;
        }
        else{
            cout<<"Invalid commmand."<<endl;
        }
        cout<<"Enter command:"<<endl;
        getline(std::cin,command);
        std::istringstream iss(command);
        (iss >> choice);
    }
    simulator.stop = true;
    simulator.extrapolate.join();
    simulator.generate_report();
    return 0;
}