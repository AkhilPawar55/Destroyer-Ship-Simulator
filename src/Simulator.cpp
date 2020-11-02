//
// Created by akhil on 5/2/2018.
//

#include "Simulator.h"
#include <chrono>
#include <pthread.h>

using std::make_unique;
using std::chrono::seconds;
using std::this_thread::sleep_for;
using std::lock_guard;

/**
 * The Simulator for the scenario
 */
Simulator::Simulator() : track_store_{}, correlation_map{}, stop{false} {
    extrapolate = thread{&Simulator::extrapolate_tracks, this};
    cout << "Constructing simulator" << endl;
}

/**
 * Check the inputs if valid
 * @param category
 * @param identity
 * @param speed
 * @return
 */
bool Simulator::validate_input(const string &category, const string &identity, const double speed) {
    if (!(category == "air" || category == "surface" || category == "subsurface") ||
        !(identity == "neutral" || identity == "friendly" || identity == "hostile")) {
        cout << "Invalid category and identity type." << endl;
        return false;
    } else if ((category == "air" || category == "surface" || category == "subsurface") &&
               (identity == "neutral" || identity == "friendly" || identity == "hostile")) {
        if (category == "air") {
            if (speed <= 50 || speed > 200) {
                cout << "Invalid speed for air target." << endl;
                return false;
            }
        }
        if (category == "surface") {
            if (speed < 0 || speed > 50) {
                cout << "Invalid speed for surface target." << endl;
                return false;
            }
        }
        if (category == "subsurface") {
            if (speed < 0 || speed > 30) {
                cout << "Invalid speed for subsurface target." << endl;
                return false;
            }
        }
    }
    return true;
}

/**
 * Create the Track with the formation from other intelligent sources or from visuals.
 * @param category
 * @param identity
 * @param speed
 */
void Simulator::add_track(const string &category, const string &identity, const double speed) {
    {
        lock_guard<mutex> lg{sync_access_mutex};
        if (validate_input(category, identity, speed))
            track_store_.push_back(make_unique<Track>(category, identity, speed));
    }
}

/**
 * Update the Track with the formation from other intelligent sources or from visuals.
 * @param track_id
 * @param category
 * @param identity
 * @param speed
 */
void Simulator::update_track(const int track_id, const string &category, const string &identity, const double speed) {
    {
        lock_guard<mutex> lg{sync_access_mutex};
        if (validate_input(category, identity, speed)) {
            for (int iter = 0; iter < track_store_.size(); ++iter) {
                if (track_store_[iter]->getShip_id_() == track_id) {
                    track_store_[iter]->setCategory_(category);
                    track_store_[iter]->setIdentity_(identity);
                    track_store_[iter]->setSpeed_(speed);
                    cout << "Track " << track_store_[iter]->getShip_id_() << " updated." << endl;
                    cout << "with attributes:" << endl;
                    cout << *track_store_[iter];
                    break;
                } else {
                    cout << "Track: " << track_id << " does not exist" << endl;
                }
            }
        }
    }
}

/**
 * Delete the Track.
 * @param track_id
 */
void Simulator::delete_track(const int track_id) {
    {
        lock_guard<mutex> lg{sync_access_mutex};
        for (auto iter = track_store_.begin(); iter != track_store_.end(); ++iter) {
            if (iter->get()->getShip_id_() == track_id) {
                cout << "Deleted " << **iter;
		iter->reset(nullptr);
                track_store_.erase(iter);
                break;
            }
        }
    }
}

/**
 * Generate a summary report when the simulation is stopped.
 */
void Simulator::generate_report() {
    {
        lock_guard<mutex> lg{sync_access_mutex};
        cout << "---Summary---" << endl;
        cout << "Tracks in the field of view are:" << endl;
        for (auto iter = track_store_.begin(); iter != track_store_.end(); ++iter) {
            cout << **iter << endl;
        }
    }
}

/**
 * Correlate the two tracks, when they are found to be the same track, but reported by diffenet sensors(radars, sonars, etc).
 * @param subject_track_id, track id of the track to be retained after correlation
 * @param object_track_id , track id of the track to be hidden after correlation
 */
void Simulator::correlate_tracks(int subject_track_id, int object_track_id) {
    {
        lock_guard<mutex> lg{sync_access_mutex};
        bool isSubFound = false;
        bool isObjFound = false;
        for (auto iter = track_store_.begin(); iter != track_store_.end(); ++iter) {
            if (iter->get()->getShip_id_() == subject_track_id) {
                isSubFound = true;
                for (auto iter_obj = track_store_.begin(); iter_obj != track_store_.end(); ++iter_obj) {
                    if (iter_obj->get()->getShip_id_() == object_track_id) {
                        isObjFound = true;
                        if (iter->get()->getCategory_() != iter_obj->get()->getCategory_() ||
                            iter->get()->getIdentity_() != iter_obj->get()->getIdentity_()) {
                            cout << "Cannot correlate as identity and/or category do not match." << endl;
                            break;
                        } else if (iter->get()->getCategory_() == iter_obj->get()->getCategory_() &&
                                   iter->get()->getIdentity_() == iter_obj->get()->getIdentity_()) {
                            //correlate
                            iter->get()->setCorrelated_track_id(object_track_id);
                            correlation_map[subject_track_id] = std::move(*iter_obj);
                            track_store_.erase(iter_obj);
                            for (auto a = correlation_map.begin(); a != correlation_map.end(); ++a) {
                                cout << "Track: " << a->first << " correlated with: " << *(a->second) << endl;
                            }
                        }
                        break;
                    }
                }
                if (!isObjFound) {
                    cout << "Subject track not found." << endl;
                }
                break;
            }
        }
        if (!isSubFound) {
            cout << "Subject track not found." << endl;
        }
    }
}

/**
 * Extrapolate(update the track's position) track over time
 */
void Simulator::extrapolate_tracks() {
    while (stop != true) {
        while (track_store_.size() > 0 && stop != true) {
            {
                lock_guard<mutex> lg{sync_access_mutex};
                for (auto iter = track_store_.begin(); iter != track_store_.end(); ++iter) {
                    iter->get()->setTime_elapsed_from_creation(
                            iter->get()->getTime_elapsed_from_creation() + 1);//increase time by 1 second
                    //calculate distance
                    // distance = speed * time.
                    iter->get()->setDistance_(iter->get()->getDistance_() +
                                              ((iter->get()->getSpeed_() *
                                                iter->get()->getTime_elapsed_from_creation()) / 3600.0));
                    check_for_de_correlation(**iter, iter->get()->getCorrelated_track_id());
                }
                for(auto iter_c = correlation_map.begin(); iter_c != correlation_map.end(); ++iter_c){
                    iter_c->second->setTime_elapsed_from_creation(
                            iter_c->second->getTime_elapsed_from_creation() + 1);//increase time by 1 second
                    //calculate distance
                    // distance = speed * time.
                    iter_c->second->setDistance_(iter_c->second->getDistance_() +
                                              ((iter_c->second->getSpeed_() *
                                                      iter_c->second->getTime_elapsed_from_creation()) / 3600.0));
                }
                remove_targets_outside_range();
            }
            sleep_for(seconds(1));
        }
    }
}

/**
 * Check if the track do not conform to the criteria's of correlation
 * @param subject_track_id, track id of the track to be retained after correlation
 * @param object_track_id , track id of the track to be hidden after correlation
 */
void Simulator::check_for_de_correlation(Track &subject, const int object_id) {
    //decorrelate
    for (auto iter = correlation_map.begin(); iter != correlation_map.end(); ++iter) {
        if (iter->first == subject.getShip_id_()) {
            if(subject.getIdentity_() != iter->second->getIdentity_() ||
               (abs(subject.getDistance_() - iter->second->getDistance_()) >= threshold_distance_correlation)){
                track_store_.push_back(make_unique<Track>(iter->second->getCategory_(),
                                                          iter->second->getIdentity_(), iter->second->getSpeed_(),
                                                          iter->second->getDistance_(), iter->second->getShip_id_()));
                cout << subject << " is decorrelated with " << *iter->second<< endl;
                subject.setCorrelated_track_id(0);
                correlation_map.erase(iter);
            }
            break;
        }
    }
}

/**
 * Remove the track's if they go beyond the ship's range(field view)
 */
void Simulator::remove_targets_outside_range() {
        for (auto iter = track_store_.begin(); iter != track_store_.end(); ++iter) {
            if (iter->get()->getDistance_() >= ship_range) {
                cout << "Deleted " << **iter;
		iter->reset(nullptr);
                track_store_.erase(iter);
                cout<<"As the target is beyond ship's range hence not significant"<<endl;
            }
        }
}
