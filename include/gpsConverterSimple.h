/***********************************************************************
 * 
 * gpsConverterSimple.h
 * 
 * A simple class for dealing with conversions between lat/lon and meters 
 * from a home location (or between two lat/lons that are in the neighborhood
 * of the home location).
 * 
 * Assumptions:
 *  - The earth is perfectly round with a fixed radius (this is false, but 
 *    it makes the math easy and fast and doesn't normally result in much 
 *    error
 *  - You are operating close to the surface of the earth (extreme altitudes
 *    not supported)
 *  - You are operating close to the home location (that you specify).  
 * 
 * This class does not do great circle math.  It does use double precision
 * floating point, and could be extended to use great circle math.  (Break
 * out that spherical law of cosines and have fun!)_
 * 
 * Author: Neil Johnson
 * 
 * Date: 2018-05-02
 * 
 * The simple math is as follows:
 * 
 * If we assume that the earth is perfectly round, then converting between
 * lat/lon and distance is as simple as doing spherical coordinate transforms.
 * 
 * To get the difference the x-direction (north/latitude):
 * 
 * x_dist = R_earth * (phi2 - phi1)
 * 
 * where phi is the latitude of each point expressed in radians.
 * 
 * The y-distance is a little trickier because the radius of each longitudinal
 * ring depends on the latitude.  We will use the latitude of the home location 
 * for simplicity:
 * 
 * y_dist = R_earth * cos(phi1) * (lambda2 - lambda1)
 * 
 * To go the other way, we simply solve for phi2 and lambda2 in the above 
 * equations.  
 *  
 **********************************************************************/

#include <cmath>

#ifndef RAD2DEG 
#define RAD2DEG (180.0/M_PI)
#endif

#ifndef DEG2RAD
#define DEG2RAD (M_PI/180.0)
#endif
 
namespace simplegps {

//! Circumference and Diameter of the earth (standard)
const double C_EARTH = 40007960;
const double R_EARTH = 6367464.59702282;
 
struct gpsLatLon {
	double lat;
	double lon;
};

//! This struct is for representing lat/lon in radians and is just for 
//! preventing RAD/DEG errors.  
struct phiLambda {
	double phi;	//! lat in radians
	double lambda; //! lon in radians
};

struct posNE {
	double pNorth;
	double pEast;
};
 
class gpsConverterSimple {
	
	static void meterDistFromLatLon(
		const gpsLatLon& homeLoc, 
		const gpsLatLon& newLoc,
		posNE& d)
	{
		//! The x-dist is very easy.  Radius of the earth times angular difference:
		phiLambda homeRad, newRad, diffRad;
		homeRad.phi = homeLoc.lat*DEG2RAD;
		homeRad.lambda = homeLoc.lon*DEG2RAD;
		newRad.phi = newLoc.lat*DEG2RAD;
		newRad.lambda = newLoc.lon*DEG2RAD;
		
		diffRad.phi = newRad.phi - homeRad.phi;
		diffRad.lambda = newRad.lambda - homeRad.lambda;
		
		d.pNorth = R_EARTH * diffRad.phi;
		d.pEast = R_EARTH * cos(homeRad.phi) * diffRad.lambda;		
	}
	
	static void LatLonFromHomeDistance(
		const posNE& d,
		const gpsLatLon& homeLoc,
		gpsLatLon& out)
	{
		phiLambda homeRad, outRad;
		homeRad.phi = homeLoc.lat*DEG2RAD;
		homeRad.lambda = homeLoc.lon*DEG2RAD;
		
		outRad.phi = homeRad.phi + d.pNorth/R_EARTH;
		outRad.lambda = homeRad.lambda + d.pEast/(R_EARTH + cos(homeRad.phi));
		
		out.lat = outRad.phi*RAD2DEG;
		out.lon = outRad.lambda*RAD2DEG;
	}
	
	 
}; //! gpsConverterSimple
 
}; //! namespace simplegps
