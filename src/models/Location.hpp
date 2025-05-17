#pragma once

class Location {
private:
    double latitude;
    double longitude;

public:
    Location(double lat = 0.0, double lon = 0.0);
    
    // Getters
    double getLatitude() const;
    double getLongitude() const;
    
    // Setters
    void setLatitude(double lat);
    void setLongitude(double lon);
    
    // Calculate distance between two locations (in kilometers)
    double distanceTo(const Location& other) const;
}; 