#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "vld.h"

USING_NS_CC;

LRESULT myWndProcHook(UINT message,WPARAM wParam,LPARAM lParam,BOOL* pProcessed);  ///new added
// uncomment below line, open debug console
// #define USE_WIN32_CONSOLE

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	eglView->setViewName("ChaosWarDemo");
    eglView->setFrameSize(480, 320);

	eglView->setWndProc(myWndProcHook); /////////////new added

    int ret = CCApplication::sharedApplication()->run();

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}




LRESULT myWndProcHook(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed)
{
	switch (message)
	{
	case WM_KEYDOWN:
	case WM_KEYUP:
		{
			//以FrameSize==DesignResolutionSize时的坐标设定
			CCPoint pt=CCPointZero;
			switch(wParam)
			{
			case 'A':
				{
					pt=ccp(25,255);
				}
				break;

			case 'D':
				{
					pt=ccp(95,256);
				}
				break;
			case 'W':
				{
					pt=ccp(63,214);
				}
				break;
			case 'S':
				{
					pt=ccp(62,290);
				}
				break;
			
			default:
				return 0;
			}
			if(GetKeyState('D') & 0x8000)
			{
				if(GetKeyState('W') & 0x8000)
				{
					pt=ccp(91,227);
				}
				else if(GetKeyState('S')& 0x8000)
				{
					pt=ccp(91,284);
				}
			}
			else if(GetKeyState('A') & 0x8000)
			{
				if(GetKeyState('W') & 0x8000)
				{
					pt=ccp(36,227);
				}
				else if(GetKeyState('S') & 0x8000)
				{
					pt=ccp(36,284);
				}

			}

			CCEGLView* eglView=CCEGLView::sharedOpenGLView();
			CCSize originalDesignResolutionSize=CCSizeMake(480,320);   //原始设计分辨率大小
			ResolutionPolicy eResolutionPolicy=kResolutionNoBorder;
			CCSize obDesignResolutionSize=eglView->getDesignResolutionSize();
			int offsetWidth=obDesignResolutionSize.width-originalDesignResolutionSize.width;
			int offsetHeight=obDesignResolutionSize.height-originalDesignResolutionSize.height;
			CCSize obScreenSize=eglView->getFrameSize();
			int offsetWidth2=obScreenSize.width-originalDesignResolutionSize.width;
			int offsetHeight2=obScreenSize.height-originalDesignResolutionSize.height;
			switch (eResolutionPolicy)
			{
			case kResolutionExactFit:
				break;
			case kResolutionNoBorder:
				pt.y+=offsetHeight;
				break;
			case kResolutionShowAll:
				pt.x+=offsetWidth2/2;
				pt.y+=offsetWidth2/2;
				break;
			case kResolutionUnKnown:
				break;
			default:
				break;
			}
			pt.x*=eglView->getScaleX();
			pt.y*=eglView->getScaleY();

			int id=wParam;
			if(message==WM_KEYDOWN)
			{
				eglView->handleTouchesBegin(1,&id,&pt.x,&pt.y);
			}
			else
			{
				eglView->handleTouchesEnd(1,&id,&pt.x,&pt.y);
			}
			*pProcessed=TRUE;
			}
			break;
		}
		return 0;
	
	}