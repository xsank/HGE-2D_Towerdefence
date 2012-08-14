#include <hge.h>
#include <hgegui.h>

class Progress:public hgeGUIObject
{
public:
	Progress(int _id,int _x,int _y,int _w,int _h,HTEXTURE _tex)
	{
		hge=hgeCreate(HGE_VERSION);
		id=_id;
		x=_x;
		y=_y;
		w=_w;
		h=_h;
		tex=_tex;
		image=new hgeSprite(tex,0,0,w,h);
		timer=0;
		curvalue=0;
		istrue=false;
	}
	~Progress();
	void Render();
	void Update();
	void Start(bool);
private:
	int id;
	int x;
	int y;
	int w;
	int h;
	HTEXTURE tex;
	HTEXTURE back_tex;
	HGE *hge;
	hgeSprite* image;
	int timer;
	int curvalue;
	bool istrue;
};