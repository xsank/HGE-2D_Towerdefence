#ifndef __ENEMY__
#define __ENEMY__




#include <hge.h>
#include <hgegui.h>
#include <hgefont.h>

class Enemy
{
public:
	int level;
	int model_id;	
	int armor;
	int hp;
	int movephase; //方向
	float x, y;//自身当前位置
	bool dead;

	Enemy() {};
	Enemy(int model_id, int round);
	~Enemy();
	void	Render(hgeFont *_fnt);
	void	Update();
	void Init();	
	bool MouseOver(float x, float y);
	void SetSelected(bool selected){this->selected = selected;};
	void SetMOver(bool mover){this->mover = mover;};
	void SetPos(float x, float y){this->x=x; this->y=y;};
	void gethit(int damage);

private:
	HGE *hge;
	HTEXTURE image_tex, ring_tex;
	hgeSprite* image, *ring;	
	bool selected;
	bool mover;
	int round;	
	float move_speed;
	float t_x, t_y;
	int r_x, r_y;
	float showphase;
};



#endif