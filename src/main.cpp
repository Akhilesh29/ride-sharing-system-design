#include <iostream>
#include "RideManager.hpp"

void printTripDetails(Trip* trip) {
    if (!trip) {
        std::cout << "Invalid trip\n";
        return;
    }
    
    std::cout << "\n------------------------\n";
    std::cout << "Trip ID: " << trip->getTripId() << "\n";
    std::cout << "Rider: " << trip->getRider()->getName() << "\n";
    if (trip->getDriver()) {
        std::cout << "Driver: " << trip->getDriver()->getName() << "\n";
    }
    std::cout << "Status: ";
    switch (trip->getStatus()) {
        case TripStatus::REQUESTED: std::cout << "Requested\n"; break;
        case TripStatus::ACCEPTED: std::cout << "Accepted\n"; break;
        case TripStatus::IN_PROGRESS: std::cout << "In Progress\n"; break;
        case TripStatus::COMPLETED: std::cout << "Completed\n"; break;
        case TripStatus::CANCELLED: std::cout << "Cancelled\n"; break;
    }
    if (trip->getStatus() == TripStatus::COMPLETED) {
        std::cout << "Fare: INR " << trip->getFare() * 82.0 << "\n"; // Converting USD to INR
    }
    std::cout << "------------------------\n";
}

int main() {
    RideManager rideManager;
    
    std::cout << "\n=== Ride Sharing System Demo ===\n";
    
    // Create users
    User* rider = new User("R001", "Parth Verma", "+91-9876543210", UserType::RIDER);
    User* driver = new User("D001", "Amrit Singh", "+91-9876543211", UserType::DRIVER);
    
    // Add users to the system
    rideManager.addUser(rider);
    rideManager.addUser(driver);
    
    // Set locations
    Location riderLocation(12.9716, 77.5946);      // Bangalore coordinates
    Location driverLocation(12.9717, 77.5947);     // Nearby location
    Location destination(12.9815, 77.6074);        // Destination in Bangalore
    
    rider->setLocation(riderLocation);
    driver->setLocation(driverLocation);
    
    std::cout << "\n1. Requesting New Trip";
    std::cout << "\nRider Location: (12.9716, 77.5946)";
    std::cout << "\nDestination: (12.9815, 77.6074)\n";
    Trip* trip = rideManager.requestTrip(rider->getId(), riderLocation, destination);
    printTripDetails(trip);
    
    std::cout << "\n2. Driver Accepting Trip";
    std::cout << "\nDriver Location: (12.9717, 77.5947)\n";
    rideManager.acceptTrip(trip->getTripId(), driver->getId());
    printTripDetails(trip);
    
    std::cout << "\n3. Starting Trip\n";
    rideManager.startTrip(trip->getTripId());
    printTripDetails(trip);
    
    std::cout << "\n4. Ending Trip\n";
    rideManager.endTrip(trip->getTripId());
    printTripDetails(trip);
    
    std::cout << "\n5. Rating System";
    std::cout << "\nRider rates driver: 5.0 stars";
    std::cout << "\nDriver rates rider: 4.5 stars\n";
    rideManager.rateTrip(trip->getTripId(), 5.0, 4.5);
    
    std::cout << "\nFinal Ratings:";
    std::cout << "\nRider (" << rider->getName() << ") rating: " << rider->getRating();
    std::cout << "\nDriver (" << driver->getName() << ") rating: " << driver->getRating();
    std::cout << "\n\n=== Demo Complete ===\n\n";
    
    return 0;
} 