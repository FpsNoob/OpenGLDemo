#pragma once
#include "basic.h"

void first_opengl(void) {
	/*�����GL_COLOR_BUFFER_BIT��ʾ�����ɫ���õ�ǰ����ɫ��䴰��*/
	glClear(GL_COLOR_BUFFER_BIT);
	/*����������������ɫ*/
	glColor3f(0.0f, 0.0f, 0.0f);
	/*��һ�����Σ��ĸ������ֱ��ʾ��λ�ڶԽ����ϵ�������ĺ�������*/
	glRectf(50.0f, 100.0f, 150.0f, 50.0f);
	/*���OpenGL���������ִ��OpenGL����*/
	glFlush();
}

