#include "Trip.hpp"

Trip::Trip(const std::string& id, User* rider, const Location& pickup, const Location& destination)
    : tripId(id), rider(rider), driver(nullptr), pickup(pickup), destination(destination),
      fare(0.0), requestTime(time(nullptr)), startTime(0), endTime(0), status(TripStatus::REQUESTED) {}

std::string Trip::getTripId() const {
    return tripId;
}

User* Trip::getRider() const {
    return rider;
}

User* Trip::getDriver() const {
    return driver;
}

Location Trip::getPickup() const {
    return pickup;
}

Location Trip::getDestination() const {
    return destination;
}

double Trip::getFare() const {
    return fare;
}

TripStatus Trip::getStatus() const {
    return status;
}

void Trip::assignDriver(User* driver) {
    if (status != TripStatus::REQUESTED) return;
    
    this->driver = driver;
    status = TripStatus::ACCEPTED;
    driver->setAvailability(false);
}

void Trip::startTrip() {
    if (status != TripStatus::ACCEPTED) return;
    
    status = TripStatus::IN_PROGRESS;
    startTime = time(nullptr);
}

void Trip::endTrip() {
    if (status != TripStatus::IN_PROGRESS) return;
    
    status = TripStatus::COMPLETED;
    endTime = time(nullptr);
    calculateFare();
    driver->setAvailability(true);
}

void Trip::cancelTrip() {
    if (status == TripStatus::COMPLETED) return;
    
    status = TripStatus::CANCELLED;
    if (driver) {
        driver->setAvailability(true);
    }
}

void Trip::calculateFare() {
    // Base fare + distance-based fare + time-based fare
    const double BASE_FARE = 5.0;
    const double PER_KM_RATE = 2.0;
    const double PER_MIN_RATE = 0.5;
    
    double distance = pickup.distanceTo(destination);
    double timeInMinutes = (endTime - startTime) / 60.0;
    
    fare = BASE_FARE + (distance * PER_KM_RATE) + (timeInMinutes * PER_MIN_RATE);
} 