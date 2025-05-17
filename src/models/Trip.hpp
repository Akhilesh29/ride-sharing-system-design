#pragma once
#include <string>
#include <ctime>
#include "Location.hpp"
#include "User.hpp"

enum class TripStatus {
    REQUESTED,
    ACCEPTED,
    IN_PROGRESS,
    COMPLETED,
    CANCELLED
};

class Trip {
private:
    std::string tripId;
    User* rider;
    User* driver;
    Location pickup;
    Location destination;
    double fare;
    time_t requestTime;
    time_t startTime;
    time_t endTime;
    TripStatus status;

public:
    Trip(const std::string& id, User* rider, const Location& pickup, const Location& destination);
    
    // Getters
    std::string getTripId() const;
    User* getRider() const;
    User* getDriver() const;
    Location getPickup() const;
    Location getDestination() const;
    double getFare() const;
    TripStatus getStatus() const;
    
    // Trip management
    void assignDriver(User* driver);
    void startTrip();
    void endTrip();
    void cancelTrip();
    
    // Fare calculation
    void calculateFare();
}; 