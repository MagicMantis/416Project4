#include "drawable.h"
#include "gamedata.h"
#include "renderContext.h"

class Rain : public Drawable {
public:
	Rain() : Drawable("rain", Vector2f(0,0), Vector2f(0,0)), length(0), wrap(0) {}
	Rain(float xp, float yp, int len, int w, float s) : 
		Drawable("rain", Vector2f(xp, yp), Vector2f(-1, float(len)*s)), length(len), wrap(w) {}
	~Rain();

	int getLength() const { return length; }

	void update(Uint32 ticks);
	void draw() const;
	const Frame* getFrame() const { return nullptr; }
private:
	int length, wrap;
};
