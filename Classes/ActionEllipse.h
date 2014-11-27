#ifndef __TP_ACTION_ELLIPSE_H__
#define __TP_ACTION_ELLIPSE_H__

#include "cocos2d.h"
#include "math\CCMath.h"
USING_NS_CC;


typedef struct {
	
	Point center;               //���ĵ�����	
	float a;                    //��Բa������
	float b;                    //��Բb�̰���
	float angle;                //��б�Ƕ�
	bool  isAnticlockwise;      //�Ƿ���ʱ���˶�
	std::pair<int, int> zOrder; //two zOrder

} EllipseConfig;


class ActionEllipse :public ActionInterval{

public:

	ActionEllipse();

	static ActionEllipse *create(float dt, const EllipseConfig& config);
	
	//�á���������ʱ�䡱�͡���Բ���Ʋ�������ʼ������
	bool initWithDurationAndConfig(float dt, const EllipseConfig& config);      
	
	virtual ActionEllipse* clone() const override;
	
	virtual ActionEllipse* reverse() const override;

	virtual void update(float t);

	virtual void startWithTarget(Node *target) override;

	
private:

	EllipseConfig _config;
	
	float getEllipsePositionX(float psai);
	
	float getEllipsePositionY(float psai); 

	float get_X_ByEllipseFormula(float psai, bool isAnticlock);

	float get_Y_ByEllipseFormula(float psai, bool isAnticlock);


private:

	CC_DISALLOW_COPY_AND_ASSIGN(ActionEllipse);

};












#endif