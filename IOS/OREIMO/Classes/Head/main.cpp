#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

static HINSTANCE main_handle = NULL;


int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	main_handle = hInstance;//������� ������� ���� �� ������� ����������
	//Magick::InitializeMagick("");

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}