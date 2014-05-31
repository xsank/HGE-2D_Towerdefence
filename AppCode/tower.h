#ifndef __TOWER__
#define __TOWER__



#include <hge.h>
#include <hgegui.h>
#include <hgefont.h>
#include <cmath>
#include "enemy.h"
#include "vector"
#include "bullet.h"

class Tower
{
public:

	//int id;
	int level;
	int model_id;	
	int atk;
	int range;

	bool bullet_hit;

	std::vector<Enemy *> TargetEnemyList;

	Tower() {};
	Tower(int model_id, float x, float y);
	~Tower();
	void	Render(hgeFont *fnt);
	void	Update();
	void Init();	
	bool MouseOver(float x, float y);
	void SetSelected(bool selected){this->selected = selected;};
	void SetMOver(bool mover){this->mover = mover;};
	void SetPos(float x, float y){this->m_x=x; this->m_y=y;};
	void SetBPos(float x, float y){this->b_x=x; this->b_y=y;};

	void DistanceCalc(Enemy * en);
	void TargetEnemyCalc();
	void SetFocus(Enemy * en){focus_e = en;};

	void LvUp();

private:
	HGE *hge;
	HTEXTURE image_tex, ring_tex;
	hgeSprite* image, *ring, *circle, *bullet;
	float m_x, m_y;//自身当前位置
	float b_x, b_y;//子弹当前位置
	float t_x, t_y;//目标当前位置
	bool selected;
	bool mover;
	Enemy * t_e, * focus_e;
	float t_e_distance;
	std::vector<Bullet *> BulletList;
	int atk_timer;
};

#endif
