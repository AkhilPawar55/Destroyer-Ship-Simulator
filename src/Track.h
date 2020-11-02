//
// Created by akhil on 5/2/2018.
//

#ifndef GRADASSIGNMENT_SHIP_H
#define GRADASSIGNMENT_SHIP_H

#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::ostream;

/**
 * Track, is the target(blip) on the radar screen.
 * Track store holds the track information of all the targets.
 *
 * @author Akhil Pawar @ RIT CS
 */
class Track {

public:

    /**
     * Create the Track supplied information.
     * @param category of the track
     * @param identity of the track
     * @param speed of the track
     */
    Track(const string &category, const string &identity, const double speed);
    /**
     *
     * @param category of the track
     * @param identity of the track
     * @param speed of the track
     * @param distance of the track from destroyer (own ship)
     * @param track_id of the track
     */
    Track(const string &category, const string &identity, const double speed, const double distance, int track_id);

    ~Track();

    /**
     * Get the track id
     * @return track id
     */
    int getShip_id_() const;

    /**
     * Get the track category
     * @return track category
     */
    const string &getCategory_() const;

    /**
     * Get the track identity
     * @return track identity
     */
    const string &getIdentity_() const;

    /**
     * Get the track speed
     * @return track speed
     */
    double getSpeed_() const;

    /**
     * Get the distance traveled by track
     * @return distance traveled by track
     */
    double getDistance_() const;

    /**
     * Get the time elapsed since creation
     * @return time elapsed since creation
     */
    long getTime_elapsed_from_creation() const;

    /**
     * Get the correlated track id
     * @return correlated track id
     */
    int getCorrelated_track_id() const;

public:
    /**
     * Set the track id
     * @param ship_id_
     */
    void setShip_id_(int ship_id_);

    /**
     * Set the track category
     * @param category_
     */
    void setCategory_(const string &category_);

    /**
     * Set the track identity
     * @param identity_
     */
    void setIdentity_(const string &identity_);

    /**
     * Set the track speed
     * @param speed_
     */
    void setSpeed_(double speed_);

    /**
     * Set the distance travelled by track
     * @param distance_
     */
    void setDistance_(double distance_);

    /**
     * Set the time elapsed since creation
     * @param time_of_creation
     */
    void setTime_elapsed_from_creation(long time_of_creation);

    /**
     * Set the track id to which the track is correlated
     * @param correlated_track_id
     */
    void setCorrelated_track_id(int correlated_track_id);

private:
    /** The track id */
    int ship_id_;

    /** The track category */
    string category_;

    /** The track identity */
    string identity_;

    /** The track speed */
    double speed_;

    /** The time elapsed since the track creation */
    long time_elapsed_from_creation;

    /** The distance traveled by track */
    double distance_;

    /** The correlated track id */
    int correlated_track_id;
public:

    /** The current running track number */
    static int id_;
};

/**
 * Print the track information
 * @param os std::ostream
 * @param t track
 * @return std::ostream
 */
ostream& operator<<(ostream& os, const Track& t);

#endif //GRADASSIGNMENT_SHIP_H
