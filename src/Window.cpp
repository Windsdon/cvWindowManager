#include "Window.h"

#include <iostream>

using namespace std;

WindowManager *WindowManager::instance = 0;

Window::Window(const string &name) :
		name(name) {
	if (!WindowManager::instance) {
		WindowManager::instance = new WindowManager;
	}
	width = 100;
	height = 100;
	id = WindowManager::instance->addWindow(*this);
}

Window::~Window() {
	WindowManager::instance->removeWindow(id);
	destroyWindow(name);
}

void Window::display(Mat image) {
	imshow(name, image);
	if (image.cols != width || image.rows != height) {
		width = image.cols;
		height = image.rows;
		WindowManager::instance->update();
	}
}

void Window::setPosition(int x, int y) {
	moveWindow(name, x, y - 30);
}

string Window::getName() {
	return name;
}

int Window::getID() {
	return id;
}

int Window::getWidth() {
	return width;
}

int Window::getHeight() {
	return height;
}

WindowManager::WindowManager() {
	screenWidth = 1920;
	screenHeight = 1080;
	spacing = 10;
}

WindowManager::~WindowManager() {
	for (unsigned int i = 0; i < windows.size(); i++) {
		delete windows.at(i);
	}
	destroyAllWindows();
}

int WindowManager::addWindow(Window &window) {
	windows.push_back(&window);
	update();
	return windows.size();
}

void WindowManager::removeWindow(int id) {
	for (vector<Window*>::iterator it = windows.begin(); it != windows.end();
			++it) {
		if ((*it)->getID() == id) {
			windows.erase(it);
		}
	}
	update();
}

void WindowManager::update() {
	vector<int> lineBreakPoints;
	vector<int> partHeight;
	int lastLineBreak = 0;
	while (true) {
		int lineSum = spacing;
		unsigned int i = lastLineBreak;
		partHeight.push_back(0);

		for (vector<Window*>::iterator it = windows.begin() + lastLineBreak;
				it != windows.end(); ++it) {
			int totalSize = spacing + (*it)->getWidth();
			if (lineSum + totalSize > screenWidth) {
				lastLineBreak = i;
				lineBreakPoints.push_back(i);
				break;
			} else {
				if (partHeight.back() < (*it)->getHeight()) {
					partHeight.back() = (*it)->getHeight();
				}

				lineSum += totalSize;
			}
			i++;
		}

		if (i == windows.size()) {
			lineBreakPoints.push_back(i);
			break;
		}
	}

	int sumHeights = 0;
	for (vector<int>::iterator it = partHeight.begin(); it != partHeight.end();
			++it) {
		sumHeights += *it;
	}

	if (sumHeights < screenHeight) {
		vector<int>::iterator itBreak = lineBreakPoints.begin(), itHeight =
				partHeight.begin();
		int positionAccum = 0, counter;
		int accumHeight = 0;

		for (; itBreak != lineBreakPoints.end();) {
			int height = *itHeight;
			int breakPoint = *itBreak;
			int accumWidth = 0;

			counter = 0;
			for (vector<Window*>::iterator it = windows.begin() + positionAccum;
					it != windows.begin() + breakPoint; ++it) {
				accumWidth += spacing;
				(*it)->setPosition(accumWidth,
						height/2 - ((*it)->getHeight() / 2) + accumHeight);
				accumWidth += (*it)->getWidth();
				counter++;
			}

			positionAccum += counter;
			accumHeight += height + 60;

			++itBreak;
			++itHeight;
		}
	} else {
		vector<int>::iterator itBreak = lineBreakPoints.begin(), itHeight =
				partHeight.begin();
		int positionAccum = 0, counter;
		int accumHeight = 0;

		for (; itBreak != lineBreakPoints.end();) {
			int height = screenHeight / lineBreakPoints.size();
			int breakPoint = *itBreak;
			int accumWidth = 0;

			counter = 0;
			for (vector<Window*>::iterator it = windows.begin() + positionAccum;
					it != windows.begin() + breakPoint; ++it) {
				accumWidth += spacing;
				(*it)->setPosition(accumWidth,
						height/2 - ((*it)->getHeight() / 2) + accumHeight);
				accumWidth += (*it)->getWidth();
				counter++;
			}

			positionAccum += counter;
			accumHeight += height;

			++itBreak;
			++itHeight;
		}
	}
}
