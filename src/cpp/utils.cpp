//
// Created by joao on 17-05-2024.
//

#include "../h/utils.h"
#include <cmath>
double Haversine(double latitude1, double longitude1,double latitude2, double longitude2)  {
    double dLat = (latitude1 - latitude2) *
                  M_PI / 180.0;
    double dLon = (longitude1 - longitude2) *
                  M_PI / 180.0;

    double lat1 = (latitude1) * M_PI / 180.0;
    double lat2 = (latitude2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);

    return 6371000 * 2 * asin(sqrt(a));
}