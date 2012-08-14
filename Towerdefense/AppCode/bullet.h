#ifndef __BULLET__
#define __BULLET__


#include <hge.h>
#include <hgegui.h>
#include <cmath>
#include "enemy.h"

class Bullet
{
public:
	Bullet(){};
	~Bullet();
	Bullet(int id, float x, float y, Enemy *em, int atk);

	void	Render();
	bool	Update();

private:
	HGE *hge;
	int model_id;
	HTEXTURE image_tex;
	hgeSprite* image;
	float b_x, b_y;
	Enemy *em;
	float m_x, m_y;
	int atk;
};


#endif
