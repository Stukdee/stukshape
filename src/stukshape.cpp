module;

#include "SDL2/SDL.h"
#include <vector>
#include <cstdio>
#include <cstring>
#include <string>

module stukshape;

namespace stukshape {



/*the function for stukshape object*/



Stukshape::Stukshape () {
	(this -> videoDriver) = NULL;
	(this -> driversCount) = 0;
}

Stukshape::~Stukshape () {
	SDL_Quit();
	fprintf(stdout,"Can't wait to meet you next time in stukshape!!!\n");
}

int Stukshape::init () {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "failed to init SDL2: %s\n",SDL_GetError());
		return -1;
	}
	fprintf(stdout,"SDL2 initialization successful\n");

	/*get information about compiled and linked of SDL2*/
	SDL_VERSION(&(this -> compiled));
	SDL_GetVersion(&(this -> linked));

	(this -> videoDriver) = SDL_GetCurrentVideoDriver();
	(this -> driversCount) = SDL_GetNumVideoDrivers();

	return 0;
}

void Stukshape::showCompiledInformation () {
	fprintf(stdout,"the version of SDL2 when be compiled: %d.%d.%d\n",
		(this -> compiled).major,
		(this -> compiled).minor,
		(this -> compiled).patch
	);
}

void Stukshape::showLinkedInformation () {
	fprintf(stdout,"the version of SDL2 when be linked: %d.%d.%d\n",
		(this -> linked).major,
		(this -> linked).minor,
		(this -> linked).patch
	);
}

void Stukshape::showVideoDriverInformation () {
	fprintf(stdout,"the video driver: %s\n",(this -> videoDriver));
}

void Stukshape::showDriverCountInformation () {
	fprintf(stdout,"the count of video driver: %d\n",(this -> driversCount));
}

void Stukshape::showVideoDriverNumber (){
	for(int i = 0;i < (this -> driversCount);i++) {
		fprintf(stdout,"%d    - %s\n",i,SDL_GetVideoDriver(i));
	}
}

void Stukshape::showAllInformation () {
	showCompiledInformation();
	showLinkedInformation();
	showVideoDriverInformation();
	showDriverCountInformation();
	showVideoDriverNumber();
}



/*the function for window object*/



Window::Window () {
	(this -> width) = 100;
	(this -> height) = 100;
	(this -> posX) = 10;
	(this -> posY) = 10;
	(this -> title) = "hello_stukshape";
	(this -> posX) = 10;
	(this -> posY) = 10;
	(this -> resizeable) = 0;
	(this -> window) = NULL;
	(this -> renderer) = NULL;
	creatWindow();
}

Window::Window (int width_,int height_,std::string title_) {
	(this -> width) = width_;
	(this -> height) = height_;
	(this -> title) = title_;
	(this -> posX) = 10;
	(this -> posY) = 10;
	(this -> resizeable) = 0;
	(this -> window) = NULL;
	(this -> renderer) = NULL;
	creatWindow();
}

Window::Window (int width_,int height_,std::string title_,int posX_,int posY_){
	(this -> width) = width_;
	(this -> height) = height_;
	(this -> title) = title_;
	(this -> posX) = posX_;
	(this -> posY) = posY_;
	(this -> resizeable) = 0;
	(this -> window) = NULL;
	(this -> renderer) = NULL;
	creatWindow();
}

Window::~Window () {
	SDL_DestroyRenderer((this -> renderer));
	SDL_DestroyWindow((this -> window));
}

int Window::creatWindow () {
	(this -> window) = SDL_CreateWindow(
		(this -> title).c_str(),
		(this -> posX),
		(this -> posY),
		(this -> width),
		(this -> height),
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);
	if ((this -> window) == NULL) {
		fprintf(stdout,"failed to creat [%s] window: %s\n",(this -> title).c_str(),SDL_GetError());
		return 1;
	}
	SDL_HideWindow((this -> window));
	return 0;
}

int Window::getDisplayModeInformation () {
	return SDL_GetWindowDisplayMode((this -> window),&(this -> displayMode));
}

void Window::showDisplayModeInformation () {
	if (getDisplayModeInformation() == 0){
		fprintf(stdout,"display mode: %dx%d @ %dHz\n",
			(this -> displayMode).w,
			(this -> displayMode).h,
			(this -> displayMode).refresh_rate
		);
	}
	else{
		fprintf(stdout,"failed to get display mode\n");
	}
}

int Window::getRendererCount () {
	return SDL_GetNumRenderDrivers();
}

void Window::showRendererCount () {
	fprintf(stdout,"the count of useable renderer: %d\n",getRendererCount());
}

std::string Window::setRenderer (std::string rendererName) {
	std::vector <int> preferredRenderer;
	for (int i = 0; i < getRendererCount();i++){
		SDL_RendererInfo info;
		if (SDL_GetRenderDriverInfo(i,&info) == 0) { 
			if (strstr(info.name,rendererName.c_str()) != NULL) {
				preferredRenderer.push_back(i);
			}
		}
	}
	for (auto it = preferredRenderer.begin();it != preferredRenderer.end();it++) {
		(this -> renderer) = SDL_CreateRenderer(
			(this -> window),
			*it,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
		);
		if ((this -> renderer) != NULL) {
			return std::string("created " + rendererName + " successfully!!!");
		}
	}
	return std::string("failed to created " + rendererName);
}

std::string Window::show () {
	SDL_ShowWindow((this -> window));
	if ((this -> renderer) == NULL){
		for(int i = 0; i < getRendererCount();i++){
			SDL_RendererInfo info;
			if(SDL_GetRenderDriverInfo(i,&info) == 0){
				allRenderer.push_back(i);
			}
		}
		if(allRenderer.size() >= 0){
			for(auto it = allRenderer.begin();it != allRenderer.end();it++){
				renderer = SDL_CreateRenderer(
					window,
					*it,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
				);
				if(renderer != NULL){
					return "created renderer successfully!!!";
				}
			}
			return "failed to created rendererT_T";
		}
	}
	return "renderer have been already!!!";
}

void Window::setResizeable (bool a){
	(this -> resizeable) = a;
	SDL_SetWindowResizable((this -> window),a ? SDL_TRUE : SDL_FALSE);
}

bool Window::isResizeable () {
	return (this -> resizeable);
}

bool Window::shouldBeClose () {
	SDL_Event e;
	if (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			return 1;
		}
	}
	return 0;
}

std::string Window::setWidth (int a) {
	if (a <= 0) {
		return std::string("the number you provide is under or equal zero.");
	}
	(this -> width) = a;
	SDL_SetWindowSize((this -> window),(this -> width),(this -> height));
	return "change size successfully";
}

std::string Window::setHeight (int a) {
	if (a <= 0) {
		return std::string("the number you provide is under or equal zero.");
	}
	(this -> height) = a;
	SDL_SetWindowSize((this -> window),(this -> width),(this -> height));
	return "change size successfully";
}

std::string Window::setSize (int a,int b) {
	if (a <= 0 or b <= 0) {
		return std::string("the number you provide is under or equal zero.");
	}
	setWidth(a);
	setHeight(b);
	return "change size successfully";
}

void Window::setTitle(std::string a) {
	SDL_SetWindowTitle((this -> window),a.c_str());
}

/*
int show_window(void){
	获取渲染器信息
	for(int i = 0; i < num_renderers;i++){
		SDL_RendererInfo info;
		if(SDL_GetRenderDriverInfo(i,&info) == 0){
			printf("  - %s\n",info.name);
			all_renderer.push_back(i);
			if(strstr(info.name, "opengl") != NULL){
				preferred_renderer.push_back(i);
				printf("找到OpenGL相关渲染驱动！值为：%d\n",i);
			}
		}
	}
	创建渲染器
	SDL_Renderer *renderer = NULL;
	if(preferred_renderer.size() >= 0){
		for(auto it = preferred_renderer.begin();it != preferred_renderer.end();it++){
			使用OpenGL驱动
			renderer = SDL_CreateRenderer(
				window,
				*it,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
			);
			if(renderer != NULL){
				printf("成功创建OpenGL渲染器。\n");
				break;
			}
			printf("%d创建失败。\n",*it);
		}
	}
	if(renderer == NULL){
		printf("OpenGL渲染器创建失败，使用之后的渲染驱动。\n");
		if(all_renderer.size() >= 0){
			for(auto it = all_renderer.begin();it != all_renderer.end();it++){
				使用接下来的驱动
				renderer = SDL_CreateRenderer(
					window,
					*it,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
				);
				if(renderer != NULL){
					printf("成功创建渲染器。\n");
					break;
				}
				printf("%d创建失败。\n",*it);
			}
		}
	}
	if(renderer == NULL){
		fprintf(stderr,"渲染器创建失败: %s\n",SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	printf("\n渲染器创建成功！\n");
	获取渲染器信息
	SDL_RendererInfo renderer_info;
	if(SDL_GetRendererInfo(renderer,&renderer_info) == 0){
		printf("当前渲染器: %s\n",renderer_info.name);
		printf("硬件加速: %s\n",(renderer_info.flags & SDL_RENDERER_ACCELERATED) ? "是" : "否");
		printf("支持VSync: %s\n",(renderer_info.flags & SDL_RENDERER_PRESENTVSYNC) ? "是" : "否");
	}
	SDL_Event e;
	int quit = 0;
	while(!quit){
		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_QUIT){
				quit = 1;
			}
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	printf("\n程序正常退出。\n");
	return 0;
}*/

}
