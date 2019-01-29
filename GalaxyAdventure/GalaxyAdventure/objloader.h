#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp> 
#include <vector>
#include <glm\gtc\matrix_transform.hpp>


/*	Zum laden eines Objektes aus einer *.obj datei

	@autor	
*/
bool loadObject(
	const char *path,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
);


