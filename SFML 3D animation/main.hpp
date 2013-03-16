//contains includes and globals
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

#include <functional>

#include <assimp\Importer.hpp>
#include <assimp\anim.h>
#include <assimp\scene.h>

#include <cstdlib>
#include <iostream>

//globals (try to keep these low)
extern Assimp::Importer importer;
//global functions