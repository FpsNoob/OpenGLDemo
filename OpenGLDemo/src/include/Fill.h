#pragma once

#include "basic.h"
#include "SqStack.h"

template<typename T> struct Seed {  //��¼���ӵ�
	T x;
	T y;
};

bool same_color(int x, int y, COLORREF color) {
	//color Ϊ�Ա���ɫ
	//��õ�ǰλ�õ�������ɫ
	int R, G, B;
	GLubyte  iPixel;
	glReadPixels(x, y, 1, 1, GL_RED, GL_UNSIGNED_BYTE, &iPixel);
	R = int(iPixel);
	glReadPixels(x, y, 1, 1, GL_GREEN, GL_UNSIGNED_BYTE, &iPixel);
	G = int(iPixel);
	glReadPixels(x, y, 1, 1, GL_BLUE, GL_UNSIGNED_BYTE, &iPixel);
	B = int(iPixel);

	if (R == GetRValue(color) && G == GetGValue(color) && B == GetBValue(color)) {
		return true;
	}
	else {
		return false;
	}
}

void edgemark_fill(int *points, COLORREF background,int n) {
	int maxX, minX, maxY, minY;
	maxX = minX = points[0];
	maxY = minY = points[1];
	for (int i = 0; i < n * 2; i += 2) {
		if (maxX < points[i]) {
			maxX = points[i];
		}
		if (minX > points[i]) {
			minX = points[i];
		}
	}
	for (int i = 1; i < n * 2; i += 2) {
		if (maxY < points[i]) {
			maxY = points[i];
		}
		if (minY > points[i]) {
			minY = points[i];
		}
	}
	for (int i = minY +1; i < maxY; i++) {
		bool inside = false;
		for (int j = minX; j <= maxX; j++) {
			if(same_color(j,i,background)){
				inside = !(inside);
			}
			if (inside) {
				glColor3f(0.0, 0.0, 1.0); //blue
				glBegin(GL_POINTS);
				glVertex2i(j, i);
				glEnd();
				glFlush();
			}
		}

	}
}

void ScanLineFill4(int x, int y, COLORREF oldcolor) {
	int xl, xr, i;    //xl��xrΪ���ε�[xl, xr]
	bool spanNeedFill;

	Seed<int> pt;              //�������ӵĽṹ
	SqStack<Seed<int>> *stack;  //����ջ
	InitStack(stack);       //��ʼ��ջ
	pt.x = x;
	pt.y = y;
	Push(stack, pt);       //��ǰ�����ɵ�����ѹ���ջ
	while (!StackEmpty(stack)) {
		Sleep(10);
		Pop(stack, pt); //ջ����ջ
		y = pt.y;
		x = pt.x;
		while (same_color(x, y, oldcolor)) {  //�������
			glColor3f(0.0, 0.0, 1.0); //blue
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
			glFlush();
			x++;
		}
		xr = x - 1;
		x = pt.x - 1;
		while (same_color(x, y, oldcolor)) {  //�������
			glColor3f(0.0, 0.0, 1.0); //blue
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
			glFlush();
			x--;
		}
		xl = x + 1;

		//������һ��ɨ����
		x = xl;
		y = y + 1;
		while (x <= xr) {
			spanNeedFill = false;
			while (same_color(x, y, oldcolor)) {
				spanNeedFill = true;
				x++;
			}
			if (spanNeedFill) {  //��ջ����������Ϊ����
				pt.x = x - 1;
				pt.y = y;
				Push(stack, pt);
				spanNeedFill = false;
			}
			while (!(same_color(x, y, oldcolor)) && x <= xr) {
				x++;
			}
		}
		//��������һ��ɨ���ߣ������봦������һ��ɨ��������
		x = xl;
		y = y - 2;
		while (x <= xr) {
			spanNeedFill = false;
			while (same_color(x, y, oldcolor)) {
				spanNeedFill = true;
				x++;
			}
			if (spanNeedFill) {
				pt.x = x - 1;
				pt. y = y;
				Push(stack, pt);
				spanNeedFill = false;
			}
			while (!(same_color(x, y, oldcolor)) && x <= xr) {
				x++;
			}
		}
	}
}


void display_fill(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0); //��ɫ
	midpoint_line(50, 50, 200, 100);
	midpoint_line(200, 100, 200, 250);
	midpoint_line(200, 250, 100, 250);
	midpoint_line(100, 250, 50, 80);
	midpoint_line(50, 80, 50, 50);


	/*�߱�־ɨ��������㷨*/
	//int points[12] = { 50,50,200,100,200,250,100,250,50,80,50,50 };
	//COLORREF background = RGB(0, 0, 0);  //��ɫ
	//int n = 6; //������
	//edgemark_fill(points, background, n);

	/*ɨ������������㷨*/
	COLORREF oldcolor = RGB(255, 255, 255);//��ɫ
	int x = 100, y = 100;
	ScanLineFill4(x, y, oldcolor);
	
}