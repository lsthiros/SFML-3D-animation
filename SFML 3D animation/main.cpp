#include "main.hpp"
#include "Model.hpp"
#include "Bone.h"
#include "Skeleton.h"
Assimp::Importer importer;

Model loadModelFromFile(char* filename);

int main(int argc, char** argv) {
	std::cerr<<"loading model"<<std::endl;
	Model model("cylinder.dae");
	std::cerr<<"classes loaded successfuly"<<std::endl;
	return 0;
}