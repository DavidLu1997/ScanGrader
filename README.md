# ScanGrader
An Optical Mark Recognition Program

ScanGrader is intended to simplify test/quiz marking for schools, being an open-source alternative for scantron.

Accuracy on a standard 50 question scan sheet approaches 100% for scanner-based deployments, and 80% using a mobile camera. Extensive calibrations are being conducted to ensure accuracy.

This is currently being developed for Windows x86.
In the future, we plan on deploying it to Linux, Windows UWP, and OS X.

Known issues can be found in [readme.txt](https://github.com/DavidLu1997/ZopperScanAPI/blob/qtGui/readme.txt)

## Compiling Instructions

### Unix
Make sure Qt is installed, consult your local package manager for details. (QtCore, QtWidgets)

Run in project root:
```bash
qmake ScanGrader.pro
make
./ScanGrader
```

### Windows
Make sure Qt (VS 2013 32bit) and Visual Studio 2013 (any edition but Express) is installed, configure Visual studio with the VS 2013 Qt Addin.

Open `ScanGrader.sln` with Visual Studio

Build and run with `ctrl-F5`, or build with `ctrl-shift-b`

^Yes, it is that simple

Or you can install one of the releases below :)

## Current Releases

[Version 1.30 Alpha](https://github.com/DavidLu1997/ZopperScanAPI/releases/tag/v1.30)

[Nightly Build (Very Unstable)](https://github.com/DavidLu1997/ScanGrader/blob/qtGui/ScanGraderSetup.msi)

## Changelog:

### 1.30
- Refactored
- Working on Linux release

### 1.23
- Fixed calibration
- Fixed ID
- Fixed speed

### 1.22
- Added progress bar
- Renamed author to Blank Space Limited

### 1.21
- Added installer 

### 1.20
- Added support for JPEG, PNG, and others
- Changed over to QImageReader
- Accuracy improved
- Speed lowered
