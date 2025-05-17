#pragma once
#include <string>
#include "Location.hpp"

enum class UserType {
    RIDER,
    DRIVER
};

class User {
private:
    std::string id;
    std::string name;
    std::string phone;
    double rating;
    int totalRatings;
    Location currentLocation;
    UserType type;
    bool isAvailable;  // for drivers

public:
    User(const std::string& id, const std::string& name, const std::string& phone, UserType type);
    
    // Getters
    std::string getId() const;
    std::string getName() const;
    std::string getPhone() const;
    double getRating() const;
    Location getLocation() const;
    UserType getType() const;
    bool getAvailability() const;
    
    // Setters
    void setLocation(const Location& location);
    void setAvailability(bool available);
    
    // Rating system
    void addRating(double newRating);
}; 