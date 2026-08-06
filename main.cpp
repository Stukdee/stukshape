#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
import stukshape;

float deltaTime = 0.0F;
float jg = 0.0F;
int w = 0;
int h = 0;

float getDeltaTime(){
	static struct timespec lastTime = {0};
	struct timespec currentTime;
	clock_gettime(CLOCK_MONOTONIC,&currentTime);
	float deltaTime = 0.0;
	if(lastTime.tv_sec != 0){
		deltaTime = (currentTime.tv_sec - lastTime.tv_sec) + (currentTime.tv_nsec - lastTime.tv_nsec) / 1e9;
	}
	lastTime = currentTime;
	return deltaTime;
}

int main(void){
	stukshape::Stukshape theMain;
	theMain.init();
	theMain.showAllInformation();
	stukshape::Window theWindow(800,800,"hello",90,90);
	theWindow.showDisplayModeInformation();
	std::cout << theWindow.setRenderer("opengl") << '\n';
	theWindow.show();
	while (!theWindow.shouldBeClose()){
		deltaTime = getDeltaTime();
		jg += deltaTime;
		if (jg > 1){
			jg = 0;
			w += 50;
			h += 50;
			theWindow.setTitle("hellocpp20");
			theWindow.setResizeable(1 - theWindow.isResizeable());
			theWindow.setWidth(w);
			theWindow.setHeight(h);
		}
	}
	return 0;
}
