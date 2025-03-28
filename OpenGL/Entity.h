#pragma once
#include "Common.h"
class Entity
{
private:
	unsigned int ID;
	Shader shader;
public:
	Entity(Shader shader,unsigned int ID );

	void Draw();

};

