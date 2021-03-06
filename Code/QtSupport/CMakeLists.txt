#///////////////////////////////////////////////////////////////////////////////
#  Copyright (c) 2010, Michael A. Jackson. BlueQuartz Software
#  All rights reserved.
#  BSD License: http://www.opensource.org/licenses/bsd-license.html
#///////////////////////////////////////////////////////////////////////////////
project(QtSupport)

if(QT4_FOUND)
    include( ${QT_USE_FILE} )
else()
    message(FATAL_ERROR "Qt 4 is Needed for this project.")
endif(QT4_FOUND)


set(Project_SRCS "")
set(Project_HDRS "")

set(QtSupport_SRCS
    ${QtSupport_SOURCE_DIR}/ApplicationAboutBoxDialog.cpp
    ${QtSupport_SOURCE_DIR}/QRecentFileList.cpp
    ${QtSupport_SOURCE_DIR}/QFileCompleter.cpp
    ${QtSupport_SOURCE_DIR}/ImageGraphicsDelegate.cpp
    ${QtSupport_SOURCE_DIR}/QFSDroppableGraphicsView.cpp
    ${QtSupport_SOURCE_DIR}/ProcessQueueDialog.cpp
    ${QtSupport_SOURCE_DIR}/ProcessQueueController.cpp
    ${QtSupport_SOURCE_DIR}/ProcessQueueTask.cpp
    ${QtSupport_SOURCE_DIR}/ColorComboPicker.cpp
    ${QtSupport_SOURCE_DIR}/QFSDropLineEdit.cpp
    ${QtSupport_SOURCE_DIR}/QProgressLabel.cpp
    ${QtSupport_SOURCE_DIR}/QDisclosableGroupBox.cpp
    ${QtSupport_SOURCE_DIR}/CheckBoxDelegate.cpp
 #   ${QtSupport_SOURCE_DIR}/LayersDockWidget.cpp
    ${QtSupport_SOURCE_DIR}/MRCInfoWidget.cpp
    ${QtSupport_SOURCE_DIR}/ImageOpenDialog.cpp
    ${QtSupport_SOURCE_DIR}/GainsOffsetsTableModel.cpp
    ${QtSupport_SOURCE_DIR}/ReconstructionArea.cpp
    ${QtSupport_SOURCE_DIR}/MRCGraphicsView.cpp
    ${QtSupport_SOURCE_DIR}/RectangleCreator.cpp
    ${QtSupport_SOURCE_DIR}/TiltAngleGroupBox.cpp
    ${QtSupport_SOURCE_DIR}/TomogramTiltLoader.cpp
    ${QtSupport_SOURCE_DIR}/ImageOpenDialog.cpp
 	${QtSupport_SOURCE_DIR}/QMRCDisplayWidget.cpp
)
set(QtSupport_HDRS
    ${QtSupport_SOURCE_DIR}/ApplicationAboutBoxDialog.h
    ${QtSupport_SOURCE_DIR}/QRecentFileList.h
    ${QtSupport_SOURCE_DIR}/QFileCompleter.h
    ${QtSupport_SOURCE_DIR}/ImageGraphicsDelegate.h
    ${QtSupport_SOURCE_DIR}/QFSDroppableGraphicsView.h
    ${QtSupport_SOURCE_DIR}/ProcessQueueDialog.h
    ${QtSupport_SOURCE_DIR}/ProcessQueueController.h
    ${QtSupport_SOURCE_DIR}/ProcessQueueTask.h
    ${QtSupport_SOURCE_DIR}/ColorComboPicker.h
    ${QtSupport_SOURCE_DIR}/QFSDropLineEdit.h
    ${QtSupport_SOURCE_DIR}/QProgressLabel.h
    ${QtSupport_SOURCE_DIR}/QDisclosableGroupBox.h
    ${QtSupport_SOURCE_DIR}/CheckBoxDelegate.h
  #  ${QtSupport_SOURCE_DIR}/LayersDockWidget.h
    ${QtSupport_SOURCE_DIR}/MRCInfoWidget.h
    ${QtSupport_SOURCE_DIR}/GainsOffsetsItemDelegate.h
    ${QtSupport_SOURCE_DIR}/GainsOffsetsTableModel.h
    ${QtSupport_SOURCE_DIR}/ReconstructionArea.h
    ${QtSupport_SOURCE_DIR}/MRCGraphicsView.h
    ${QtSupport_SOURCE_DIR}/RectangleCreator.h
    ${QtSupport_SOURCE_DIR}/TiltAngleGroupBox.h
    ${QtSupport_SOURCE_DIR}/TomogramTiltLoader.h
    ${QtSupport_SOURCE_DIR}/ImageOpenDialog.h
 	${QtSupport_SOURCE_DIR}/QMRCDisplayWidget.h
)
cmp_IDE_SOURCE_PROPERTIES("QtSupport" "${QtSupport_HDRS}" "${QtSupport_SRCS}" "0")


# --------------------------------------------------------------------
# The UI files As generated by Qt Designer
# --------------------------------------------------------------------
SET( QtSupport_QT_UI_FILES
  ${QtSupport_SOURCE_DIR}/UI_Files/ApplicationAboutBoxDialog.ui
  ${QtSupport_SOURCE_DIR}/UI_Files/ImageOpenDialog.ui
#  ${QtSupport_SOURCE_DIR}/UI_Files/LayersDockWidget.ui
  ${QtSupport_SOURCE_DIR}/UI_Files/MRCInfoWidget.ui
  ${QtSupport_SOURCE_DIR}/UI_Files/MRCTiltInfo.ui
  ${QtSupport_SOURCE_DIR}/UI_Files/ProcessQueueDialog.ui
  ${QtSupport_SOURCE_DIR}/UI_Files/TiltAngleGroupBox.ui
  ${QtSupport_SOURCE_DIR}/UI_Files/TomogramTiltLoader.ui
  ${QtSupport_SOURCE_DIR}/UI_Files/ImageOpenDialog.ui
  ${QtSupport_SOURCE_DIR}/UI_Files/QMRCDisplayWidget.ui
)
cmp_IDE_SOURCE_PROPERTIES( "QtSupport/UI_Files" "${QtSupport_QT_UI_FILES}" "" "0")

# and finally any resource files
#SET( QtSupport_RCS ${PROJECT_RESOURCES_DIR}/icons/images/Icons.qrc)

# --------------------------------------------------------------------
# Run on the files
#QT4_ADD_RESOURCES( QtSupport_Generated_RC_SRCS ${QCrossCorrelation_RCS} )

# --------------------------------------------------------------------
# this will run uic on .ui files:
QT4_WRAP_UI( QtSupport_Generated_UI_HDRS ${QtSupport_QT_UI_FILES} )

# --------------------------------------------------------------------
# and finally this will run moc:
QT4_WRAP_CPP( QtSupport_Generated_MOC_SRCS ${QtSupport_HDRS} )

# --------------------------------------------------------------------
#-- Put the generated files into their own group for IDEs
cmp_IDE_SOURCE_PROPERTIES( "Generated" "${QtSupport_Generated_UI_HDRS}" "${QtSupport_Generated_MOC_SRCS};${QtSupport_Generated_RC_SRCS}" "0")



set(Project_SRCS ${Project_SRCS}
        ${QtSupport_SRCS}
        ${QtSupport_HDRS}
        ${QtSupport_Generated_UI_HDRS}
        ${QtSupport_Generated_MOC_SRCS}
        )

include_directories(${QtSupport_SOURCE_DIR})
include_directories(${QtSupport_SOURCE_DIR}/..)
include_directories(${QtSupport_BINARY_DIR})
include_directories(${QtSupport_BINARY_DIR}/..)
add_definitions(-DQT_CORE_LIB)

add_library(QtSupport STATIC ${Project_SRCS})
target_link_libraries(QtSupport
                    ${QT_QTCORE_LIBRARY}
                    ${QT_QTGUI_LIBRARY}
                    )

LibraryProperties( QtSupport ${EXE_DEBUG_EXTENSION})


