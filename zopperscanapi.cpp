#include "zopperscanapi.hpp"

ZopperScanAPI::ZopperScanAPI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//Add navbar to window
	navbar = new NavBar();
	setCentralWidget(navbar);

	//Hide toolbar
	ui.mainToolBar->hide();

	//Hide status bar
	statusBar()->hide();

	//Set Title
	setWindowTitle(tr("ScanGrader v%1").arg(version));
}

ZopperScanAPI::~ZopperScanAPI()
{
	delete navbar;
}
