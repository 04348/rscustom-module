#include "module.h"
#include <iostream>

IModule * CreateModule()
{
	return new Module();
}

Module::Module()
{
	this->version = 0;
	this->version_target = 0;
	this->name = "Skyrim";
	this->author = "Grenbur";
}

