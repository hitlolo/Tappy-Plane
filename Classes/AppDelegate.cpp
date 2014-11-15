#include "AppDelegate.h"
#include "LogoScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director

//#if (CC_TARGET_PLATFORM !=CC_TARGET_WIN32)//Android下需要复制数据文件
//	//检查数据库文件是否已经提取
//	if (isFileExist("image.json") == false)
//	{
//		copyData("image.json");//要使用的sqlite库文件
//	}
//#endif


	std::vector<std::string> paths;
	paths.push_back("fonts");
	paths.push_back("image");
	paths.push_back("sounds");
	FileUtils::getInstance()->setSearchPaths(paths);

    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
		glview->setFrameSize(800,480);
        director->setOpenGLView(glview);
		
    }
	glview->setDesignResolutionSize(800, 480, ResolutionPolicy::FIXED_WIDTH);
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	auto scene = LogoScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

