#include "s3e.h"
#include "IwGx.h"

#include "design.h"

struct CTouchb {
    int32 x;
    int32 y;
    bool active;
    int32 id;
} g_Touches;

void SingleTouchMotionCB(s3ePointerMotionEvent* event) {
    g_Touches.x = event->m_x;
    g_Touches.y = event->m_y;
}

void SingleTouchButtonCB(s3ePointerEvent* event) {
    g_Touches.active = event->m_Pressed != 0;
    g_Touches.x = event->m_x;
    g_Touches.y = event->m_y;
}

int main() {
    IwGxInit();
    IwGxSetColClear(0, 0, 0xff, 0xff);
        
    while(!s3eDeviceCheckQuitRequest()
          && !(s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
          && !(s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)
          ) {
        IwGxClear();

		s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)SingleTouchButtonCB, NULL);
        IwGxPrintString(g_Touches.x, g_Touches.y, "Hello, World!");
		drawBoard();

        IwGxFlush();
        IwGxSwapBuffers();
        s3eDeviceYield(0);	
    }
    IwGxTerminate();
    return 0;
}
