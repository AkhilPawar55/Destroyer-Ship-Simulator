//
// Created by akhil on 5/2/2018.
//

#ifndef GRADASSIGNMENT_SIMULATOR_H
#define GRADASSIGNMENT_SIMULATOR_H

#include "Track.h"
#include <vector>
#include <memory>
#include <map>
#include <thread>
#include <mutex>

using std::stringstream;
using std::vector;
using std::unique_ptr;
using std::map;
using std::thread;
using std::mutex;

/**
 * The simulator is the INS Kolkata Destroyer Class Simulator.
 * It has a collection of targets, that may be air, surface or subsurface in it field of veiw
 *
 * @author Akhil Pawar @ RIT CS
 */
class Simulator{
public:
    /**
     * The Simulator for the scenario
     */
    Simulator();

    /**
     * Create the Track with the formation from other intelligent sources or from visuals.
     * @param category
     * @param identity
     * @param speed
     */
    void add_track(const string& category, const string& identity, const double speed);

    /**
     * Update the Track with the formation from other intelligent sources or from visuals.
     * @param track_id
     * @param category
     * @param identity
     * @param speed
     */
    void update_track(const int track_id, const string& category, const string& identity, const double speed);

    /**
     * Delete the Track.
     * @param track_id
     */
    void delete_track(const int track_id);

    /**
     * Check the inputs if valid
     * @param category
     * @param identity
     * @param speed
     * @return
     */
    bool validate_input(const string& category, const string& identity, const double speed);

    /**
     * Correlate the two tracks, when they are found to be the same track, but reported by diffenet sensors(radars, sonars, etc).
     * @param subject_track_id, track id of the track to be retained after correlation
     * @param object_track_id , track id of the track to be hidden after correlation
     */
    void correlate_tracks(int subject_track_id, int object_track_id);

    /**
     * Extrapolate(update the track's position) track over time
     */
    void extrapolate_tracks();

    /**
     * Check if the track do not conform to the criteria's of correlation
     * @param subject_track_id, track id of the track to be retained after correlation
     * @param object_track_id , track id of the track to be hidden after correlation
     */
    void check_for_de_correlation(Track& subject, const int object_id);

    /**
     * Remove the track's if they go beyond the ship's range(field view)
     */
    void remove_targets_outside_range();

    /**
     * Generate a summary report when the simulation is stopped.
     */
    void generate_report();

    /** thread to extrapolate the tracks */
    thread extrapolate;

    /** indicator for stopped simulation */
    bool stop;

    /** mutex to access the track_store */
    mutex sync_access_mutex;
private:

    /** The track store, collection of the tracks */
    vector<unique_ptr<Track>> track_store_;

    /** The collection of tracks which are correlated */
    map<int,unique_ptr<Track>> correlation_map;

    /** The ship's max range */
    const double ship_range = 1000.0; //miles

    /** The distance threshold for correlation criteria */
    const double threshold_distance_correlation = 50.0;
};


#endif //GRADASSIGNMENT_SIMULATOR_H
