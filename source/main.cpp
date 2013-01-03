#include "fControl.h"
#include "s3e.h"
#include "IwGx.h"

struct CTouchb {
    int32 x;
    int32 y;
    bool active;
    int32 id;
} g_Touches;

void SingleTouchButtonCB(s3ePointerEvent* event) {
    g_Touches.active = event->m_Pressed != 0;
    g_Touches.x = event->m_x;
    g_Touches.y = event->m_y;
}

int main() {
	fControl gameControl;
	gameControl.viewInit();
        
    while(!s3eDeviceCheckQuitRequest()
          && !(s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
          && !(s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)
          ) {
		gameControl.viewClear();

		s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)SingleTouchButtonCB, NULL);

		gameControl.drawBoard();
		gameControl.drawNumbers();

		gameControl.viewFlush();
    }
    gameControl.viewKill();
    return 0;
}
