#ifndef __TP_ACTION_ELLIPSE_H__
#define __TP_ACTION_ELLIPSE_H__

#include "cocos2d.h"
#include "math\CCMath.h"
USING_NS_CC;


typedef struct {
	
	Point center;               //中心点坐标	
	float a;                    //椭圆a长半轴
	float b;                    //椭圆b短半轴
	float angle;                //倾斜角度
	bool  isAnticlockwise;      //是否逆时针运动
	std::pair<int, int> zOrder; //two zOrder

} EllipseConfig;


class ActionEllipse :public ActionInterval{

public:

	ActionEllipse();

	static ActionEllipse *create(float dt, const EllipseConfig& config);
	
	//用“动作持续时间”和“椭圆控制参数”初始化动作
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