# ScanGrader
An Optical Mark Recognition Program

ScanGrader is intended to simplify test/quiz marking for schools, being an open-source alternative for scantron.

Accuracy on a standard 50 question scan sheet approaches 100% for scanner-based deployments, and 80% using a mobile camera. Extensive calibrations are being conducted to ensure accuracy.

This is currently being developed for Windows x86 and Unix using C++ and Qt 5.5.

Future releases may involve C# and CUDA.

Sample files can be found in Images.

## Compiling Instructions

For all platforms, please ensure that [Qt 5.5](http://www.qt.io/qt5-5/) is installed with at least QtCore and QtWidgets.

### Unix

Run in project root:
```bash
qmake ScanGrader.pro
make
./ScanGrader
```

### Windows (Visual Studio)

Make sure Visual Studio 2013 (any edition but Express) is installed, configure Visual studio with the [VS Qt Addin](http://download.qt.io/official_releases/vsaddin/qt-vs-addin-1.2.5.exe).

Open `ScanGrader.sln` with Visual Studio

Build and run with `ctrl-F5`, or build with `ctrl-shift-b`

Adjust paths as necessary.

### Windows (Qt Creator)

Make sure Qt Creator is installed, it comes packaged with Qt.

Open `ScanGrader.pro` with Qt Creator.

Build and run.

Adjust paths as necessary.

## Current Releases

- [Version 1.0.1](https://github.com/DavidLu1997/ZopperScanAPI/releases/tag/v1.0.1)
- [Nightly Build (Very Unstable)](https://github.com/DavidLu1997/ScanGrader/blob/qtGui/ScanGraderSetup.msi)

## Changelog:

### v1.0.1
- Bugfix for certain operating systems
- JPEGs did not load on Windows 10 and Windows 8
- Packaged Qt's JPEG plugin

### v1.0.0
- Changed versioning system
- Added multi-platform compilation support
- Revamped GUI slightly

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
