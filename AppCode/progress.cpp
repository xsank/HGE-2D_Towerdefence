#include "progress.h"

Progress::~Progress()
{
	hge->Release();
}

void Progress::Render()
{
	image->Render(x,y);
}

void Progress::Update()
{
	if(istrue)
	{
		timer++;
		if(timer%60==0)
			curvalue++;
		if(curvalue<=300)
			image->Render(x+curvalue,y);
		else
			image->Render(x+300,y);
	}
	else
		image->Render(x,y);
}

void Progress::Start(bool flag)
{
	istrue=flag;
}