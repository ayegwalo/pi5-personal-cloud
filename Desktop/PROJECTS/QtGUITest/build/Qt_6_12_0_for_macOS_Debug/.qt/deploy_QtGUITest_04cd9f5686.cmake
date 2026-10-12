include("/Users/ayegwalo/Desktop/PROJECTS/QtGUITest/build/Qt_6_12_0_for_macOS_Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/QtGUITest-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "QtGUITest.app"
)
