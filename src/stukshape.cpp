#include "SDL2/SDL.h"
#include <vector>
#include <cstdio>
#include <cstring>
#include "stukshape.h"
namespace stukshape{
int show_window(void){
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		fprintf(stderr, "SDL初始化失败: %s\n",SDL_GetError());
		return -1;
	}
	printf("SDL2 初始化成功！\n");
	SDL_version compiled;
	SDL_version linked;
	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("\n编译时的SDL2版本: %d.%d.%d\n",
		compiled.major,
		compiled.minor,
		compiled.patch
	);
	printf("链接时的SDL2版本: %d.%d.%d\n",
		linked.major,
		linked.minor,
		linked.patch
	);
	/* 获取当前视频驱动信息*/
	const char *video_driver = SDL_GetCurrentVideoDriver();
	printf("当前视频驱动: %s\n",video_driver ? video_driver : "未知");
	/* 获取可用的视频驱动*/
	int num_drivers = SDL_GetNumVideoDrivers();
	printf("可用的视频驱动数量: %d\n",num_drivers);
	for(int i = 0;i < num_drivers;i++) {
		printf("  - %s\n",SDL_GetVideoDriver(i));
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"0");
	/* 创建窗口*/
	SDL_Window *window = NULL;
	window = SDL_CreateWindow(
		"SDL2 测试窗口",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800,
		800,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);
	if(window == NULL) {
		fprintf(stderr,"窗口创建失败: %s\n",SDL_GetError());
		SDL_Quit();
		return 1;
	}
	printf("\n窗口创建成功！\n");
	printf("窗口大小: %dx%d\n",800,800);
	/* 获取窗口信息*/
	SDL_DisplayMode display_mode;
	if(SDL_GetWindowDisplayMode(window,&display_mode) == 0){
		printf("显示模式: %dx%d @ %dHz\n",
			display_mode.w,
			display_mode.h,
			display_mode.refresh_rate
		);
	}
	/* 获取渲染器信息*/
	std::vector <int> preferred_renderer;
	std::vector <int> all_renderer;
	int num_renderers = SDL_GetNumRenderDrivers();
	printf("\n可用的渲染驱动数量: %d\n",num_renderers);
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
	/* 创建渲染器*/
	SDL_Renderer *renderer = NULL;
	if(preferred_renderer.size() >= 0){
		for(auto it = preferred_renderer.begin();it != preferred_renderer.end();it++){
			/* 使用OpenGL驱动*/
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
				/* 使用接下来的驱动*/
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
	/*获取渲染器信息*/
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
}
}
