include("/home/nabeel_okal/Qt_Projects/AR4_PickAndPlace/build/Desktop_Qt_6_9_1-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/AR4_PickAndPlace-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/nabeel_okal/Qt_Projects/AR4_PickAndPlace/build/Desktop_Qt_6_9_1-Debug/AR4_PickAndPlace
    GENERATE_QT_CONF
)
