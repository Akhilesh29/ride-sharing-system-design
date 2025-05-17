#include "User.hpp"

User::User(const std::string& id, const std::string& name, const std::string& phone, UserType type)
    : id(id), name(name), phone(phone), rating(5.0), totalRatings(0), type(type), isAvailable(true) {}

std::string User::getId() const {
    return id;
}

std::string User::getName() const {
    return name;
}

std::string User::getPhone() const {
    return phone;
}

double User::getRating() const {
    return rating;
}

Location User::getLocation() const {
    return currentLocation;
}

UserType User::getType() const {
    return type;
}

bool User::getAvailability() const {
    return isAvailable;
}

void User::setLocation(const Location& location) {
    currentLocation = location;
}

void User::setAvailability(bool available) {
    isAvailable = available;
}

void User::addRating(double newRating) {
    if (newRating < 1.0 || newRating > 5.0) return;
    
    double totalScore = rating * totalRatings;
    totalRatings++;
    rating = (totalScore + newRating) / totalRatings;
} 