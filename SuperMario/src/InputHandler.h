#include <list>
#include "header.h"

class CInputHandler
{
public:
	std::list<Action>* getActions();

private:
	std::list<Action> actions;
};