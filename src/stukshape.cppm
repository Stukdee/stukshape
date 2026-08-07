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
		introduction : just creat a class.
		*/
		Stukshape ();

		/*
		function : ~Stukshape ()
		introduction : quit SDL2.
		*/
		~Stukshape ();

		/*
		function : init ()
		introduction : to init this object and SDL2.
		out : the status of the function, when the value smaller than 0, it is failed to init.
		*/
		int init ();

		/*
		function : showCompiledInformation () const
		introduction : print the version of SDL2 when it is compiled.
		*/
		void showCompiledInformation () const;

		/*
		function : showLinkedInformation () const
		introduction : print the version of SDL2 when it is linked.
		*/
		void showLinkedInformation () const;

		/*
		function : showVideoDriverInformation () const
		introduction : print the information of video driver which is being used now.
		*/
		void showVideoDriverInformation () const;

		/*
		function : showDriverCountInformation () const
		introduction : print the count of all the video drivers which can be found.
		*/
		void showDriverCountInformation () const;

		/*
		function : showVideoDriverNumber () const
		introduction : print the number of video driver.
		*/
		void showVideoDriverNumber () const;

		/*
		function : showAllInformation () const
		introduction : print all the information about this object.
		*/
		void showAllInformation () const;
};

class Window{

	private:

		/*the width of the window*/
		int width;

		/*the height of the window*/
		int height;

		/*the title of the window*/
		std::string title;

		/*the position x on the screen*/
		int posX;

		/*the position y on the screen*/
		int posY;

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

		/*as its name*/
		bool resizeable;

		/*to creat window,it is must not be provided to user*/
		int creatWindow ();

		/*to get display mode information,it is must not be provided to user*/
		int getDisplayModeInformation ();

	public:

		/*
		function : Window ()
		introduction : default function without input when the window is created.
		*/
		Window ();

		/*
		function : Window (int width_,int height_,std::string title_)
		introduction : user shoude provide 3 values to set the window.
		in : 
			width_ -> provide window with its width
			height_ -> provide window with its height
			title_ -> provide window with its title
		*/
		Window (int width_,int height_,std::string title_);

		/*
		function : Window (int width_,int height_,std::string title_,int posX_,int posY_)
		introduction : user shoude provide 5 values to set the window.
		in : 
			width_ -> provide window with its width
			height_ -> provide window with its height
			title_ -> provide window with its title
			posX_ -> provide window with its position x on the screen
			posY_ -> provide window with its position y on the screen
		*/
		Window (int width_,int height_,std::string title_,int posX_,int posY_);

		/*
		function : ~Window ()
		introduction : to destroy the renderer and window.
		*/
		~Window ();

		/*
		function : showDisplayModeInformation ()
		introduction : show the display mode information.
			it should be used after using the function show().
		*/
		void showDisplayModeInformation ();

		/*
		function : getRendererCount ()
		introduction : it will get the count of the renderer.
		out : an integer about the count of renderer.
		*/
		int getRendererCount ();

		/*
		function : showRendererCount ()
		introduction : it will show the count of the renderer.
		*/
		void showRendererCount ();

		/*
		function : int setRenderer (std::string rendererName)
		introduction : provide it with a name of the renderer, it can find and switch itself.
		in : 
			rendererName -> a string witch is the name of the renderer
		out : a status about this function
		*/
		std::string setRenderer (std::string rendererName);

		/*
		function : void show ()
		introduction : show the window if it is ready.
		out : a status about this function
		*/
		std::string show ();

		/*
		function : void setResizeable (bool a)
		introduction : set the window s resizeable.
		in :
			a -> a bool value, true for it can resize,
				false for it cant
		*/
		void setResizeable (bool a = 0);

		/*
		function : bool isResizeable ()
		introduction : return a bool value to tell user the resizeable.
		out : a bool value, true for it can resize, false for it cant resize
		*/
		bool isResizeable ();

		/*
		function : shouldBeClose ()
		introduction : it is used to check the window if it should be close.
			i advise user using it with "while()".
		out : an bool value, true for it should, false for it shouldn't
		*/
		bool shouldBeClose ();

		/*
		function : void setWidth (int w)
		introduction : it can change the window s width.
		in : 
			a -> window s width
		out : the status about the function, if you input a number under 0, it donest work.
		*/
		std::string setWidth (int a = 100);

		/*
		function : void setHeight (int a)
		introduction : it can change the window s height.
		in : 
			a -> window s height
		out : the status about the function, if you input a number under 0, it donest work.
		*/
		std::string setHeight (int a = 100);

		/*
		function : void setSize (int a,int b)
		introduction : it can change both width and height.
		in : 
			a -> width
			b -> height
		out : the status about the function, if you input a number under 0, it donest work.
		*/
		std::string setSize (int a = 100,int b = 100);

		/*
		function : void setTitle(std::string a)
		introduction : it can change the window s title.
		in : 
			a -> the new title for the window
		*/
		void setTitle(std::string a = "hello");
};

int show_window(void);
}
