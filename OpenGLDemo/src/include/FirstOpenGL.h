#pragma once
#include "basic.h"

void first_opengl(void) {
	/*清除，GL_COLOR_BUFFER_BIT表示清除颜色，用当前背景色填充窗口*/
	glClear(GL_COLOR_BUFFER_BIT);
	/*三个参数来设置颜色*/
	glColor3f(0.0f, 0.0f, 0.0f);
	/*画一个矩形，四个参数分别表示了位于对角线上的两个点的横纵坐标*/
	glRectf(50.0f, 100.0f, 150.0f, 50.0f);
	/*清空OpenGL命令缓冲区，执行OpenGL命令*/
	glFlush();
}

