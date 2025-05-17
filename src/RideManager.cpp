#include "RideManager.hpp"
#include <algorithm>
#include <random>

RideManager::RideManager() {}

RideManager::~RideManager() {
    // Cleanup memory
    for (auto driver : drivers) delete driver;
    for (auto rider : riders) delete rider;
    for (auto& pair : activeTrips) delete pair.second;
    for (auto& pair : tripHistory) delete pair.second;
}

void RideManager::addUser(User* user) {
    if (user->getType() == UserType::DRIVER) {
        drivers.push_back(user);
    } else {
        riders.push_back(user);
    }
}

void RideManager::removeUser(const std::string& userId) {
    auto removeFromVector = [userId](std::vector<User*>& users) {
        auto it = std::find_if(users.begin(), users.end(),
            [userId](const User* user) { return user->getId() == userId; });
        if (it != users.end()) {
            delete *it;
            users.erase(it);
        }
    };
    
    removeFromVector(drivers);
    removeFromVector(riders);
}

User* RideManager::getUser(const std::string& userId) {
    for (auto driver : drivers) {
        if (driver->getId() == userId) return driver;
    }
    for (auto rider : riders) {
        if (rider->getId() == userId) return rider;
    }
    return nullptr;
}

User* RideManager::findNearestDriver(const Location& pickup) const {
    User* nearestDriver = nullptr;
    double minDistance = std::numeric_limits<double>::max();
    
    for (auto driver : drivers) {
        if (!driver->getAvailability()) continue;
        
        double distance = driver->getLocation().distanceTo(pickup);
        if (distance < minDistance) {
            minDistance = distance;
            nearestDriver = driver;
        }
    }
    
    return nearestDriver;
}

std::string RideManager::generateTripId() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 35); // 0-9 and A-Z
    
    std::string id;
    for (int i = 0; i < 8; ++i) {
        int r = dis(gen);
        id += r < 10 ? '0' + r : 'A' + (r - 10);
    }
    return id;
}

Trip* RideManager::requestTrip(const std::string& riderId, const Location& pickup, const Location& destination) {
    User* rider = getUser(riderId);
    if (!rider || rider->getType() != UserType::RIDER) return nullptr;
    
    User* driver = findNearestDriver(pickup);
    if (!driver) return nullptr;
    
    std::string tripId = generateTripId();
    Trip* trip = new Trip(tripId, rider, pickup, destination);
    trip->assignDriver(driver);
    
    activeTrips[tripId] = trip;
    return trip;
}

bool RideManager::acceptTrip(const std::string& tripId, const std::string& driverId) {
    auto it = activeTrips.find(tripId);
    if (it == activeTrips.end()) return false;
    
    Trip* trip = it->second;
    User* driver = getUser(driverId);
    
    if (!driver || driver->getType() != UserType::DRIVER) return false;
    
    trip->assignDriver(driver);
    return true;
}

bool RideManager::startTrip(const std::string& tripId) {
    auto it = activeTrips.find(tripId);
    if (it == activeTrips.end()) return false;
    
    it->second->startTrip();
    return true;
}

bool RideManager::endTrip(const std::string& tripId) {
    auto it = activeTrips.find(tripId);
    if (it == activeTrips.end()) return false;
    
    Trip* trip = it->second;
    trip->endTrip();
    
    // Move to history
    tripHistory[tripId] = trip;
    activeTrips.erase(it);
    
    return true;
}

bool RideManager::cancelTrip(const std::string& tripId) {
    auto it = activeTrips.find(tripId);
    if (it == activeTrips.end()) return false;
    
    Trip* trip = it->second;
    trip->cancelTrip();
    
    // Move to history
    tripHistory[tripId] = trip;
    activeTrips.erase(it);
    
    return true;
}

void RideManager::updateDriverLocation(const std::string& driverId, const Location& newLocation) {
    User* driver = getUser(driverId);
    if (driver && driver->getType() == UserType::DRIVER) {
        driver->setLocation(newLocation);
    }
}

void RideManager::rateTrip(const std::string& tripId, double riderRating, double driverRating) {
    Trip* trip = getTrip(tripId);
    if (!trip) return;
    
    if (trip->getStatus() == TripStatus::COMPLETED) {
        trip->getRider()->addRating(riderRating);
        trip->getDriver()->addRating(driverRating);
    }
}

Trip* RideManager::getTrip(const std::string& tripId) const {
    auto it = activeTrips.find(tripId);
    if (it != activeTrips.end()) return it->second;
    
    auto historyIt = tripHistory.find(tripId);
    if (historyIt != tripHistory.end()) return historyIt->second;
    
    return nullptr;
}

std::vector<Trip*> RideManager::getUserTrips(const std::string& userId) const {
    std::vector<Trip*> userTrips;
    
    auto checkAndAddTrip = [&userTrips, &userId](Trip* trip) {
        if (trip->getRider()->getId() == userId || 
            (trip->getDriver() && trip->getDriver()->getId() == userId)) {
            userTrips.push_back(trip);
        }
    };
    
    for (const auto& pair : activeTrips) {
        checkAndAddTrip(pair.second);
    }
    
    for (const auto& pair : tripHistory) {
        checkAndAddTrip(pair.second);
    }
    
    return userTrips;
} 