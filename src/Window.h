/*
 * Window.h
 *
 *  Created on: 05/09/2013
 *      Author: windsdon
 */

#pragma once

#include <string>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;

class Window {
public:
	Window(const string &name);
	~Window();

	void display(Mat image);

	string getName();
	int getID();

	int getWidth();
	int getHeight();
	void setPosition(int x, int y);

private:
	const string name;
	int id;
	int width, height;
};

class WindowManager {
public:
	WindowManager();
	~WindowManager();

	int addWindow(Window &window);
	void update();
	void removeWindow(int id);

	static WindowManager *instance;
private:
	int screenWidth, screenHeight;
	int spacing;
	vector<Window*> windows;
	WindowManager(WindowManager&);
};

