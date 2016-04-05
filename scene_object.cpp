/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements scene_object.h

***********************************************************/

#include <cmath>
#include <iostream>
#include "scene_object.h"

bool UnitSquare::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
	// TODO: implement intersection code for UnitSquare, which is
	// defined on the xy-plane, with vertices (0.5, 0.5, 0), 
	// (-0.5, 0.5, 0), (-0.5, -0.5, 0), (0.5, -0.5, 0), and normal
	// (0, 0, 1).
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.
    
    Point3D rayOrigin = worldToModel * ray.origin;
    Vector3D dir = worldToModel * ray.dir;
    Vector3D origin(rayOrigin[0], rayOrigin[1], rayOrigin[2]);
    
    double t = -(origin[2]) / dir[2];
    
    if (t <= 0) {
        // Intersection behind gaze direction
        return false;
    }
    
    double x = origin[0] + t * dir[0];
    double y = origin[1] + t * dir[1];
    
    
    if (x <= 0.5 && x >= -0.5 && y <= 0.5 && y >= -0.5) {
        // Intersection has occured
        Point3D intersect(x, y, 0);
        Vector3D normal(0, 0, 1);
        if (ray.intersection.none || t < ray.intersection.t_value) {
            ray.intersection.point = modelToWorld * intersect;
            ray.intersection.normal = worldToModel.transpose() * normal;
            ray.intersection.normal.normalize();
            ray.intersection.t_value = t;
            ray.intersection.none = false;
            return true;
        }
    }

	return false;
}

bool UnitSphere::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
	// TODO: implement intersection code for UnitSphere, which is centred 
	// on the origin.  
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.
    
    // Source: http://stackoverflow.com/questions/6533856/ray-sphere-intersection
    // Transfrom the ray to object space
    Point3D rayOrigin = worldToModel * ray.origin;
    Vector3D dir = worldToModel * ray.dir;
    Vector3D origin(rayOrigin[0], rayOrigin[1], rayOrigin[2]);
    
    dir.normalize();
    double a = 1; // normalized
    double b = dir.dot(origin) * 2;
    double c = origin.dot(origin) - 1;
    
    double delta = b * b - 4 * c;
    
    if (delta < 0) {
        // No intersection
        return false;
    }
    
    double d1 = (-b - sqrt(delta)) / 2;
    double d2 = (-b + sqrt(delta)) / 2;
    double d = fmin(d1, d2); // Choose the closer one.
    
    if (d <= 0)
        return false;
    
    double x = origin[0] + d * dir[0];
    double y = origin[1] + d * dir[1];
    double z = origin[2] + d * dir[2];
    Point3D intersect(x, y, z);
    Vector3D normal(intersect[0], intersect[1], intersect[2]);
    normal = worldToModel.transpose() * normal;
    
    if (ray.intersection.none || d < ray.intersection.t_value) {
        ray.intersection.point = modelToWorld * intersect;
        ray.intersection.normal = normal;
        ray.intersection.normal.normalize();
        ray.intersection.none = false;
        ray.intersection.t_value = d;
        return true;
    }
    
	return false;
}

