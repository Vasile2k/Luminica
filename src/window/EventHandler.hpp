#pragma once

class EventHandler {

public:

	virtual void onKey(int key, int scancode, int action, int modifiers) {};
	virtual void onMouseButton(int button, int action, int modifiers) {};
	virtual void onCursorPosition(double xPos, double yPos) {};
	virtual void onScroll(double xPos, double yPos) {};
	virtual ~EventHandler() {};

};
