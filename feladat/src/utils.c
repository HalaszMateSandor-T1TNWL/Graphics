#include "Utils/utils.h"
/*
*    The sin() and cos() functions like radians so I have to convert the numbers into radians
*    it's also just a lot more comfortable and readable if the user can see/give the value in
*                               a format they can actually comprehend
*/
double degree_to_radian(double degree) {
    return (degree * M_PI)/180.0;
}