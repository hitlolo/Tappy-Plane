#ifndef __TP_ACTION_ROTATE_H__
#define __TP_ACTION_ROTATE_H__


#include "cocos2d.h"

USING_NS_CC;

class ActionRotation :public ActionInterval{

public:

	static ActionRotation* create(Action* action);

	bool initWithAction(Action* action);

	virtual void startWithTarget(Node* target) override;

	virtual bool isDone(void) const override;

	virtual void step(float dt) override;

	~ActionRotation();

private:

	void    setTargetParllelAction(Action* action);

	Node*   targetNode;

	Action* targetAction;

};





#endif