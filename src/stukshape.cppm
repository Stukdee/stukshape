/*
plan : make API for SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"0");
*/

module;

#include "SDL2/SDL.h"
#include <string>
#include <vector>

export module stukshape;

export namespace stukshape {

class Stukshape {

	private:
		/*the version of SDL2 when it is compiled*/
		SDL_version compiled;
		/*the version of SDL2 when it is linked*/
		SDL_version linked;
		/*the information of video driver which is being used now*/
		const char *videoDriver;
		/*the count of all the video drivers which can be found*/
		int driversCount;

	public:

		/*
		function : Stukshape ()
		Introduction : just creat a class.
		*/
		Stukshape ();

		/*
		function : ~Stukshape ()
		Introduction : quit SDL2.
		*/
		~Stukshape ();

		/*
		function : init ()
		Introduction : to init this object and SDL2.
		out : the status of the function, when the value smaller than 0, it is failed to init.
		*/
		int init ();

		/*
		function : showCompiledInformation ()
		Introduction : print the version of SDL2 when it is compiled.
		*/
		void showCompiledInformation ();

		/*
		function : showLinkedInformation ()
		Introduction : print the version of SDL2 when it is linked.
		*/
		void showLinkedInformation ();

		/*
		function : showVideoDriverInformation ()
		Introduction : print the information of video driver which is being used now.
		*/
		void showVideoDriverInformation ();

		/*
		function : showDriverCountInformation ();
		Introduction : print the count of all the video drivers which can be found.
		*/
		void showDriverCountInformation ();

		/*
		function : showVideoDriverNumber ();
		Introduction : print the number of video driver.
		*/
		void showVideoDriverNumber ();

		/*
		function : showAllInformation ();
		Introduction : print all the information about this object.
		*/
		void showAllInformation ();
};

class Window{

	private:

		/*the width of the window*/
		int width;

		/*the height of the window*/
		int height;

		/*the title of the window*/
		std::string title;

		/*the window*/
		SDL_Window *window;

		/*the display mode of the window*/
		SDL_DisplayMode displayMode;

		/*the renderer*/
		SDL_Renderer *renderer;

		/*the vector will be used to store all the renderer 's number*/
		std::vector <int> allRenderer;

		/*just count of renderer*/
		int rendererCount;

		/*to creat window,it is must not be provided to user*/
		int creatWindow ();

		/*to get display mode information,it is must not be provided to user*/
		int getDisplayModeInformation ();

	public:

		/*
		function : Window ()
		Introduction : default function without input when the window is created.
		*/
		Window ();

		/*
		function : Window (int width_,int height_,std::string title_)
		Introduction : user shoude provide 3 values to set the window.
		in : 
			width_ -> provide window with its width
			height_ -> provide window with its height
			title_ -> provide window with its title
		*/
		Window (int width_,int height_,std::string title_);

		/*
		function : ~Window ()
		Introduction : to destroy the renderer and window.
		*/
		~Window ();

		/*
		function : showDisplayModeInformation ()
		Introduction : show the display mode information.
			it should be used after using the function show().
		*/
		void showDisplayModeInformation ();

		/*
		function : getRendererCount ()
		Introduction : it will get the count of the renderer.
		out : an integer about the count of renderer.
		*/
		int getRendererCount ();

		/*
		function : showRendererCount ()
		Introduction : it will show the count of the renderer.
		*/
		void showRendererCount ();

		/*
		function : void show ()
		Introduction : show the window if it is ready.
		*/
		void show ();

		/*
		function : shouldBeClose ()
		Introduction : it is used to check the window if it should be close.
			i advise user using it with "while()".
		out : an bool value, true for it should, false for it shouldn't
		*/
		bool shouldBeClose ();
		/*
		void setWidth();
		void setHeight();
		void setTitle();*/
};

int show_window(void);
}
