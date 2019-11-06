#pragma once
#include "basic.h"

#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

class wcPt2D {
public:
	float x, y;
};

const int winLeftBitCode = 0x1;
const int winRightBitCode = 0x2;
const int winBottomBitCode = 0x4;
const int winTopBitCode = 0x8;

GLubyte encode(wcPt2D pt, wcPt2D winMin, wcPt2D winMax) {    //���б���
	GLubyte code = 0x00;
	if (pt.x < winMin.x)        //D0=1,����Ϊ0
		code = code | winLeftBitCode;
	if (pt.x > winMax.x)        //D1=1,����Ϊ0
		code = code | winRightBitCode;
	if (pt.y < winMin.y)        //D2=1,����Ϊ0
		code = code | winBottomBitCode;
	if (pt.y > winMax.y)        //D3=1,����Ϊ0
		code = code | winTopBitCode;
	return (code);
}

inline int inside(int code) {               //���ڲ���inside=1
	return int(!code);
}

inline int reject(int code1, int code2) {   //code1&code2������0������������reject=true
	return int(code1 & code2);
}

inline int accept(int code1, int code2) {   //code1|code2����0������ȡ����accept=true
	return int(!(code1 | code2));
}

void swapPts(wcPt2D *p1, wcPt2D *p2) {      //��������ֵ
	wcPt2D tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void swapCodes(GLubyte *c1, GLubyte *c2) {   //��������
	GLubyte tmp;
	tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

void lineClip(wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2)    //�ü�
{
	GLubyte code1, code2;
	int done = false, plotLine = false;
	float m;
	while (!done)                       //��֤���µ�P1P2���½��м���
	{
		code1 = encode(p1, winMin, winMax);   //��p1��p2���б��룬�ֱ�Ϊcode1��code2
		code2 = encode(p2, winMin, winMax);
		if (accept(code1, code2))		//��ֱ��P1P2����ȡ��֮
		{
			done = true;
			plotLine = true;
		}
		else if (reject(code1, code2)) //��ֱ��P1P2��������֮
		{
			done = true;
		}
		else                           //����
		{
			if (inside(code1))         //��P1�ڴ����ڣ��򽻻�P1��P2������ֵ�ͱ���
			{
				swapPts(&p1, &p2);
				swapCodes(&code1, &code2);
			}

			//�ж�P1�ڴ�������һ�࣬Ȼ��������ߵĽ��㣬���ý����ֵ���P1������ֵ���Դﵽȥ��P1S�߶ε�Ŀ��
			if (p2.x != p1.x)
				m = (p2.y - p1.y) / (p2.x - p1.x);
			if (code1 & winLeftBitCode)
			{
				p1.y += (winMin.x - p1.x) * m;
				p1.x = winMin.x;
			}
			else if (code1 & winRightBitCode)
			{
				p1.y += (winMax.x - p1.x) * m;
				p1.x = winMax.x;
			}
			else if (code1 & winBottomBitCode)
			{
				if (p2.x != p1.x)
					p1.x += (winMin.y - p1.y) / m;
				p1.y = winMin.y;
			}
			else if (code1 & winTopBitCode)
			{
				if (p2.x != p1.x)
					p1.x = (winMax.y - p1.y) / m;
				p1.y = winMax.y;
			}
		}
	}
	//���»��Ƶ�ǰ��ֱ�߶�P1P2
	if (plotLine)
		glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();
}

void drawpolygon(double cd[])
{
	glBegin(GL_LINE_LOOP);    //����ֱ��
	glLineWidth(10);
	for (int i = 0; i < 8; i = i + 2) {
		glVertex2f(cd[i], cd[i + 1]);
	}
	glEnd();
}

void drawline(double cd[])
{
	glBegin(GL_LINES);      //���Ƶ�
	glLineWidth(10);
	for (int i = 0; i < 8; i = i + 2) {
		glVertex2f(cd[i], cd[i + 1]);
	}
	glEnd();
}

void myKeyBoard(unsigned char key, int x, int y) //��������Ϣ
{
	wcPt2D winMin = { 200, 200 };
	wcPt2D winMax = { 400, 400 };
	wcPt2D p1 = { 100, 0 };
	wcPt2D p2 = { 420, 300 };

	if (key == 13)   //����Enter��
		lineClip(winMin, winMax, p1, p2);

	glFlush();
	if (key == 27)   //����ESC��
		exit(0);
}
void display(void)
{
	double re[8] = { 200, 200, 400, 200, 400, 400, 200, 400 };   //���ձ������
	
    double line[4] = {0,0 , 500, 500};

	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 600, 600);
	glColor3f(0, 0, 0);
	//����
	drawpolygon(re);
	drawline(line);

	glFlush();
}




