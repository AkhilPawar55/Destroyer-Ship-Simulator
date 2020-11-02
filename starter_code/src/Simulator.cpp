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
Simulator::Simulator() {
    //implement
}

/**
 * Check the inputs if valid
 * @param category
 * @param identity
 * @param speed
 * @return
 */
bool Simulator::validate_input(const string &category, const string &identity, const double speed) {
    //implement
}

/**
 * Create the Track with the formation from other intelligent sources or from visuals.
 * @param category
 * @param identity
 * @param speed
 */
void Simulator::add_track(const string &category, const string &identity, const double speed) {
    //implement
}

/**
 * Update the Track with the formation from other intelligent sources or from visuals.
 * @param track_id
 * @param category
 * @param identity
 * @param speed
 */
void Simulator::update_track(const int track_id, const string &category, const string &identity, const double speed) {
    //implement
}

/**
 * Delete the Track.
 * @param track_id
 */
void Simulator::delete_track(const int track_id) {
    //implement
}

/**
 * Generate a summary report when the simulation is stopped.
 */
void Simulator::generate_report() {
    {
        //implement
    }
}

/**
 * Correlate the two tracks, when they are found to be the same track, but reported by diffenet sensors(radars, sonars, etc).
 * @param subject_track_id, track id of the track to be retained after correlation
 * @param object_track_id , track id of the track to be hidden after correlation
 */
void Simulator::correlate_tracks(int subject_track_id, int object_track_id) {
    
        //implement
   
}

/**
 * Extrapolate(update the track's position) track over time
 */
void Simulator::extrapolate_tracks() {
	//distance = speed * time
	//sleep for 1 second between extrapolation cycles
    //implement
}

/**
 * Check if the track do not conform to the criteria's of correlation
 * @param subject_track_id, track id of the track to be retained after correlation
 * @param object_track_id , track id of the track to be hidden after correlation
 */
void Simulator::check_for_de_correlation(Track &subject, const int object_id) {
    //decorrelate
    //implement
}

/**
 * Remove the track's if they go beyond the ship's range(field view)
 */
void Simulator::remove_targets_outside_range() {
        //implement
}
