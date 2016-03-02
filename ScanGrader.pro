TEMPLATE = app
TARGET = ScanGrader
INCLUDEPATH += .
CONFIG += c++11
QT += widgets

# Input
HEADERS += scangrader.hpp \
           ui_scangrader.h \
           GeneratedFiles/ui_scangrader.h \
           guiElements/AboutWidget.hpp \
           guiElements/ConfigFileWidget.hpp \
           guiElements/ConfigWidget.hpp \
           guiElements/ExportWidget.hpp \
           guiElements/ImagePreview.hpp \
           guiElements/ImageWidget.hpp \
           guiElements/KeyFileWidget.hpp \
           guiElements/KeyWidget.hpp \
           guiElements/NavBar.hpp \
           guiElements/OptionWidget.hpp \
           guiElements/ResultWidget.hpp \
           guiElements/ScanFileWidget.hpp \
           guiElements/ScanGuiIncludes.hpp \
           ScanAPI/AnalyzeImage.hpp \
           ScanAPI/Headers.hpp \
           ScanAPI/ImageTemplate.hpp \
           ScanAPI/Pixel.hpp \
           ScanAPI/Point.hpp \
           ScanAPI/ReadDot.hpp \
           ScanAPI/Rectangle.hpp \
           ScanAPI/ScanImage.hpp
FORMS += scangrader.ui
SOURCES += main.cpp \
           scangrader.cpp \
           GeneratedFiles/qrc_scangrader.cpp \
           guiElements/AboutWidget.cpp \
           guiElements/ConfigFileWidget.cpp \
           guiElements/ConfigWidget.cpp \
           guiElements/ExportWidget.cpp \
           guiElements/ImagePreview.cpp \
           guiElements/ImageWidget.cpp \
           guiElements/KeyFileWidget.cpp \
           guiElements/KeyWidget.cpp \
           guiElements/NavBar.cpp \
           guiElements/OptionWidget.cpp \
           guiElements/ResultWidget.cpp \
           guiElements/ScanFileWidget.cpp \
           ScanAPI/AnalyzeImage.cpp \
           ScanAPI/ImageTemplate.cpp \
           ScanAPI/ReadDot.cpp \
           ScanAPI/ScanImage.cpp
RESOURCES += scangrader.qrc
