
#include <hge.h>
#include <hgegui.h>


#define HGESLIDER_BAR			0
#define HGESLIDER_BARRELATIVE	1
#define HGESLIDER_SLIDER		2

/*
** optSlider
*/
class optSlider : public hgeGUIObject
{
public:
	optSlider(int id, float x, float y, float w, float h, HTEXTURE tex, float tx, float ty, float sw, float sh, bool vertical=false);
	virtual			~optSlider();

	void			SetMode(float _fMin, float _fMax, int _mode) { fMin=_fMin; fMax=_fMax; mode=_mode; }
	void			SetValue(float _fVal);
	float			GetValue() const { return fVal; }

	virtual void	Render();
	virtual bool	MouseMove(float x, float y);
	virtual bool	MouseLButton(bool bDown);

private:
	bool			bPressed;
	bool			bVertical;
	int			mode;
	float			fMin, fMax, fVal;
	float			sl_w, sl_h;
	hgeSprite		*sprSlider;
};
