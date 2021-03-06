#ifndef NF_H_
#define NF_H_ 1

#pragma once

#include <string>
#include <assert.h>
#include <list>

#include <json_spirit/json_spirit.h>
#include <json_spirit/value.h>
#include <json_spirit/writer.h>

#include "constants.h"

#include "implementation.h"

using namespace std;
using namespace json_spirit;

class Implementation;

class NF
{
private:
	/**
	*	@brief: name of the NF
	*/
	string name;
	
	list<Implementation*> implementations;
	
public:
	NF(string name);
	void addImplementation(Implementation *implementation);
	
	string getName();
	
	Object toJSON();
};

#endif //NF_H_
