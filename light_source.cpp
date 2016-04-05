/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements light_source.h

***********************************************************/

#include <cmath>
#include "light_source.h"

void PointLight::shade( Ray3D& ray ) {
	// TODO: implement this function to fill in values for ray.col 
	// using phong shading.  Make sure your vectors are normalized, and
	// clamp colour values to 1.0.
	//
	// It is assumed at this point that the intersection information in ray 
	// is available.  So be sure that traverseScene() is called on the ray 
	// before this function.
    
    // Source: https://steveharveynz.wordpress.com/category/programming/c-raytracer/
    
    Material* material = ray.intersection.mat;

    Colour dif_col = _col_diffuse * material->diffuse;
    Colour spe_col = _col_specular * material->specular;
    Colour amb_col = _col_ambient * material->ambient;
    
    Vector3D normal = ray.intersection.normal;
    normal.normalize();
    
    Vector3D light = _pos - ray.intersection.point;
    light.normalize();
    
    // Eyepoint vector
    Vector3D eye = -ray.dir;
    eye.normalize();
    
    // Relection vector
    Vector3D reflection = (2 * light.dot(normal)) * normal - light;
    reflection.normalize();
    
    double dif_comp = normal.dot(light);
    dif_comp = fmax(0, dif_comp);
    
    double spe_comp = pow(reflection.dot(eye), material->specular_exp);
    spe_comp = fmax(0, spe_comp);
    
    Colour diffuse = dif_comp * dif_col;
    Colour specular = spe_comp * spe_col;
    Colour ambient = amb_col;
    
    Colour illuminate = ambient + diffuse + specular;
    illuminate.clamp();
    ray.col = illuminate;
}


