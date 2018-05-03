#include <iostream>
#include <iomanip>

#include "gpsConverterSimple.h"

int main(void)
{
	simplegps::latLon homeLoc = {.lat = 40.575415, .lon = -111.974169};
	
	simplegps::latLon NLoc = {.lat = 40.584413209, .lon = -111.974169};
	
	simplegps::latLon ELoc = {.lat = 40.575415, .lon = -111.96232224}; 
	
	simplegps::latLon SLoc = {.lat = 40.566416791, .lon = -111.974169};
	
	simplegps::latLon WLoc = {.lat = 40.575415, .lon = -111.98601576};
	
	//! First, Test that we get the right distances for 1000 m for each of the points above.  
	std::cout << "LatLon Distance calculation test: " << std::endl;
	
	simplegps::posNE d;
	simplegps::meterDistFromLatLon(homeLoc, NLoc, d);	
	std::cout << "  North Point Distances from Home: " << d << " (Should be 1000 N, 0 E)" << std::endl;
	
	simplegps::meterDistFromLatLon(homeLoc, ELoc, d);
	std::cout << "  East Point  Distances from Home: " << d << " (Should be 0 N, 1000 E)" << std::endl;
	
	simplegps::meterDistFromLatLon(homeLoc, SLoc, d);
	std::cout << "  South Point Distances from Home: " << d << " (Should be -1000 N, 0 E)" << std::endl;
	
	simplegps::meterDistFromLatLon(homeLoc, WLoc, d);
	std::cout << "  West Point  Distances from Home: " << d << " (Should be 0 N, -1000 E)" << std::endl;
	
	std::cout << std::endl;
	
	//! Now the off-axis directions:
	simplegps::latLon NELoc = {.lat = 40.584413209, .lon = -111.96232224};
	
	simplegps::latLon SELoc = {.lat = 40.566416791, .lon = -111.96232224};
	
	simplegps::latLon SWLoc = {.lat = 40.566416791, .lon = -111.98601576}; 	
	
	simplegps::latLon NWLoc = {.lat = 40.584413209, .lon = -111.98601576};
	
	//! First, Test that we get the right distances for 1000 m for each of the points above.  
	std::cout << "LatLon Distance calculation test: " << std::endl;
	
	simplegps::meterDistFromLatLon(homeLoc, NELoc, d);	
	std::cout << "  NorthEast Point Distances from Home: " << d << " (Should be 1000 N, 1000 E)" << std::endl;
	
	simplegps::meterDistFromLatLon(homeLoc, SELoc, d);
	std::cout << "  SouthEast Point  Distances from Home: " << d << " (Should be -1000 N, 1000 E)" << std::endl;
	
	simplegps::meterDistFromLatLon(homeLoc, SWLoc, d);
	std::cout << "  SouthWest Point Distances from Home: " << d << " (Should be -1000 N, -1000 E)" << std::endl;
	
	simplegps::meterDistFromLatLon(homeLoc, NWLoc, d);
	std::cout << "  NorthWest Point  Distances from Home: " << d << " (Should be 1000 N, -1000 E)" << std::endl;
	
	std::cout << std::endl;
		
	//! Next, test the inverse (getting new lat lon from given distance):
	d = {.pNorth = 1000, .pEast = 0};
	simplegps::latLon newLoc;
	simplegps::LatLonFromHomeDistance(d, homeLoc, newLoc);
	std::cout.precision(11);
	std::cout << "  North 1000 m: " << newLoc << " (should be about 40.584413, -111.974169)\n";
	
	d = {.pNorth = 0, .pEast = 1000};
	simplegps::LatLonFromHomeDistance(d, homeLoc, newLoc);
	std::cout << "  East 1000 m: " << newLoc << " (should be about 40.575415, -111.96232224)\n";
	
	d = {.pNorth = -1000, .pEast = 0};
	simplegps::LatLonFromHomeDistance(d, homeLoc, newLoc);
	std::cout << "  South 1000 m: " << newLoc << " (should be about 40.5664200, -111.974169)\n";
	
	d = {.pNorth = 0, .pEast = -1000};
	simplegps::LatLonFromHomeDistance(d, homeLoc, newLoc);
	std::cout << "  West 1000 m: " << newLoc << " (should be about 40.575415, -111.98601576)\n";
	
	std::cout << "\nOff Axis:\n";
	d = {.pNorth = 1000, .pEast = 1000};
	simplegps::LatLonFromHomeDistance(d, homeLoc, newLoc);
	std::cout << "  NorthEast 1000 m: " << newLoc << " (should be about 40.584413209, -111.96232224)\n";
	
	d = {.pNorth = -1000, .pEast = 1000};
	simplegps::LatLonFromHomeDistance(d, homeLoc, newLoc);
	std::cout << "  SouthEast 1000 m: " << newLoc << " (should be about 40.566416791, -111.96232224)\n";

	d = {.pNorth = -1000, .pEast = -1000};
	simplegps::LatLonFromHomeDistance(d, homeLoc, newLoc);
	std::cout << "  SouthWest 1000 m: " << newLoc << " (should be about 40.566416791, -111.98601576)\n";

	d = {.pNorth = 1000, .pEast = -1000};
	simplegps::LatLonFromHomeDistance(d, homeLoc, newLoc);
	std::cout << "  NorthWest 1000 m: " << newLoc << " (should be about 40.584413209, -111.98601576)\n";
	
	
	
	return 0;
}
