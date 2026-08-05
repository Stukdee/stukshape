import stukshape;

int main(void){
	stukshape::Stukshape theMain;
	theMain.init();
	theMain.showAllInformation();
	stukshape::Window theWindow(400,400,"hello");
	theWindow.show();
	theWindow.showDisplayModeInformation();
	while (!theWindow.shouldBeClose()){}
	return 0;
}
