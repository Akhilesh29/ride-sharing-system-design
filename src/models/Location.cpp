#include "Location.hpp"
#include <cmath>

#define PI 3.14159265358979323846
#define EARTH_RADIUS 6371.0 // Earth's radius in kilometers

Location::Location(double lat, double lon) : latitude(lat), longitude(lon) {}

double Location::getLatitude() const {
    return latitude;
}

double Location::getLongitude() const {
    return longitude;
}

void Location::setLatitude(double lat) {
    latitude = lat;
}

void Location::setLongitude(double lon) {
    longitude = lon;
}

double Location::distanceTo(const Location& other) const {
    // Using Haversine formula to calculate distance between two points on Earth
    double lat1 = latitude * PI / 180.0;
    double lat2 = other.latitude * PI / 180.0;
    double lon1 = longitude * PI / 180.0;
    double lon2 = other.longitude * PI / 180.0;

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = sin(dlat/2) * sin(dlat/2) +
               cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    
    return EARTH_RADIUS * c;
} 