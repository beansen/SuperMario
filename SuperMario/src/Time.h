#include "header.h"

class CTime
{
public:
	CTime();
	float getDeltaTime();
	void startFrame();
	void endFrame();

private:
	Uint32 frameStartTime;
	Uint32 frameTime;
};