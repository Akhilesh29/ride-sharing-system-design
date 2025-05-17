#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "models/User.hpp"
#include "models/Trip.hpp"

class RideManager {
private:
    std::vector<User*> drivers;
    std::vector<User*> riders;
    std::unordered_map<std::string, Trip*> activeTrips;
    std::unordered_map<std::string, Trip*> tripHistory;
    
    // Helper methods
    User* findNearestDriver(const Location& pickup) const;
    std::string generateTripId() const;

public:
    RideManager();
    ~RideManager();
    
    // User management
    void addUser(User* user);
    void removeUser(const std::string& userId);
    User* getUser(const std::string& userId);
    
    // Trip management
    Trip* requestTrip(const std::string& riderId, const Location& pickup, const Location& destination);
    bool acceptTrip(const std::string& tripId, const std::string& driverId);
    bool startTrip(const std::string& tripId);
    bool endTrip(const std::string& tripId);
    bool cancelTrip(const std::string& tripId);
    
    // Location updates
    void updateDriverLocation(const std::string& driverId, const Location& newLocation);
    
    // Rating system
    void rateTrip(const std::string& tripId, double riderRating, double driverRating);
    
    // Trip queries
    Trip* getTrip(const std::string& tripId) const;
    std::vector<Trip*> getUserTrips(const std::string& userId) const;
}; 