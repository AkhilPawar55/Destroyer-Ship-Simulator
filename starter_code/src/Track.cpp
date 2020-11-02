//
// Created by akhil on 5/2/2018.
//

#include "Track.h"

int Track::id_ = 0;

/**
 * Create the Track supplied information.
 * @param category
 * @param identity
 * @param speed
 * @param distance
 * @param id
 */
Track::Track(const string &category, const string &identity, const double speed, const double distance, int id) {
    //implement
}

/**
 * Create the Track supplied information.
 * @param category
 * @param identity
 * @param speed
 */
Track::Track(const string &category, const string &identity, const double speed) {
	//implement
}

Track::~Track() {

}

/**
 * Get the track id
 * @return track id
 */
int Track::getShip_id_() const {
    return ship_id_;
}

/**
 * Get the track category
 * @return track category
 */
const string &Track::getCategory_() const {
    return category_;
}

/**
 * Get the track identity
 * @return track identity
 */
const string &Track::getIdentity_() const {
    return identity_;
}

/**
 * Get the track speed
 * @return track speed
 */
double Track::getSpeed_() const {
    return speed_;
}

/**
 * Set the track id
 * @param ship_id_
 */
void Track::setShip_id_(int ship_id_) {
    Track::ship_id_ = ship_id_;
}

/**
 * Set the track category
 * @param category_
 */
void Track::setCategory_(const string &category_) {
    Track::category_ = category_;
}

/**
 * Set the track speed
 * @param speed_
 */
void Track::setIdentity_(const string &identity_) {
    Track::identity_ = identity_;
}

/**
 * Set the track speed
 * @param speed_
 */
void Track::setSpeed_(double speed_) {
    Track::speed_ = speed_;
}

/**
 * Get the distance traveled by track
 * @return distance traveled by track
 */
double Track::getDistance_() const {
    return distance_;
}

/**
 * Get the time elapsed since creation
 * @return time elapsed since creation
 */
long Track::getTime_elapsed_from_creation() const {
    return time_elapsed_from_creation;
}

/**
 * Set the distance travelled by track
 * @param distance_
 */
void Track::setDistance_(double distance_) {
    Track::distance_ = distance_;
}

/**
 * Set the time elapsed since creation
 * @param time_of_creation
 */
void Track::setTime_elapsed_from_creation(long time_of_creation) {
    Track::time_elapsed_from_creation = time_of_creation;
}

/**
 * Get the correlated track id
 * @return correlated track id
 */
int Track::getCorrelated_track_id() const {
    return correlated_track_id;
}

/**
 * Set the track id to which the track is correlated
 * @param correlated_track_id
 */
void Track::setCorrelated_track_id(int correlated_track_id) {
    Track::correlated_track_id = correlated_track_id;
}

/**
 * Print the track information
 * @param os std::ostream
 * @param t track
 * @return std::ostream
 */
ostream &operator<<(ostream &os, const Track &t) {
    os << "Track: " << t.getShip_id_() << "\n\tcategory: " << t.getCategory_() << "\n\tidentity: " << t.getIdentity_()
       << "\n\tspeed: " << t.getSpeed_() << "\n\tdistance: " << t.getDistance_() << endl;
    return os;
}