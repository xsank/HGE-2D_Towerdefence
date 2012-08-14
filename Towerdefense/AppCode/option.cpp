#include "option.h"

/*
** optSlider
*/
optSlider::optSlider(int _id, float x, float y, float w, float h, HTEXTURE tex, float tx, float ty, float sw, float sh, bool vertical)
{
	id=_id;
	bStatic=false;
	bVisible=true;
	bEnabled=true;
	bPressed=false;
	bVertical=vertical;
	rect.Set(x, y, x+w, y+h);

	mode=HGESLIDER_BAR;
	fMin=0; fMax=100; fVal=50;
	sl_w=sw; sl_h=sh;

	sprSlider=new hgeSprite(tex, tx, ty, sw, sh);
}

optSlider::~optSlider()
{
	if(sprSlider) delete sprSlider;
}

void optSlider::SetValue(float _fVal)
{
	if(_fVal<fMin) fVal=fMin;
	else if(_fVal>fMax) fVal=fMax;
	else fVal=_fVal;
}

void optSlider::Render()
{
	float xx, yy;
	float x1,y1,x2,y2;

	xx=rect.x1+(rect.x2-rect.x1)*(fVal-fMin)/(fMax-fMin);
	yy=rect.y1+(rect.y2-rect.y1)*(fVal-fMin)/(fMax-fMin);

	if(bVertical)
		switch(mode)
	{
		case HGESLIDER_BAR: x1=rect.x1; y1=rect.y1; x2=rect.x2; y2=yy; break;
		case HGESLIDER_BARRELATIVE: x1=rect.x1; y1=(rect.y1+rect.y2)/2; x2=rect.x2; y2=yy; break;
		case HGESLIDER_SLIDER: x1=(rect.x1+rect.x2-sl_w)/2; y1=yy-sl_h/2; x2=(rect.x1+rect.x2+sl_w)/2; y2=yy+sl_h/2; break;
	}
	else
		switch(mode)
	{
		case HGESLIDER_BAR: x1=rect.x1; y1=rect.y1; x2=xx; y2=rect.y2; break;
		case HGESLIDER_BARRELATIVE: x1=(rect.x1+rect.x2)/2; y1=rect.y1; x2=xx; y2=rect.y2; break;
		case HGESLIDER_SLIDER: x1=xx-sl_w/2; y1=(rect.y1+rect.y2-sl_h)/2; x2=xx+sl_w/2; y2=(rect.y1+rect.y2+sl_h)/2; break;
	}

	sprSlider->RenderStretch(x2-sl_w, y1, x2, y2);  //对于横版滑动条的改动，，对于竖版失效
}

bool optSlider::MouseLButton(bool bDown)
{
	bPressed=bDown;
	return false;
}

bool optSlider::MouseMove(float x, float y)
{
	if(bPressed)
	{
		bPressed=false;
		if(bVertical)
		{
			
			if(y>rect.y2-rect.y1) y=rect.y2-rect.y1;
			if(y<0) y=0;
			fVal=fMin+(fMax-fMin)*y/(rect.y2-rect.y1);
		}
		else
		{
			if(x>rect.x2-rect.x1) x=rect.x2-rect.x1;
			if(x<0) x=0;
			fVal=fMin+(fMax-fMin)*x/(rect.x2-rect.x1);
		}
		return true;
	}
	return false;
}
