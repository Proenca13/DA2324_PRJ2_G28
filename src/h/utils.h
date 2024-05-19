//
// Created by joao on 17-05-2024.
//

#ifndef DA2324_PRJ2_G28_UTILS_H
#define DA2324_PRJ2_G28_UTILS_H
/**
 * @brief Calculates the Haversine distance between two points on the Earth's surface.
 *
 * The Haversine formula determines the great-circle distance between two points on a sphere given
 * their longitudes and latitudes. The function returns the distance in meters.
 *
 * @param latitude1 Latitude of the first point in degrees.
 * @param longitude1 Longitude of the first point in degrees.
 * @param latitude2 Latitude of the second point in degrees.
 * @param longitude2 Longitude of the second point in degrees.
 * @return double The distance between the two points in meters.
 */
double Haversine(double latitude1, double longitude1,double latitude2, double longitude2);
#endif //DA2324_PRJ2_G28_UTILS_H
