# Common source files for both CLI and non-CLI execautables
set(CLISOURCEFILES
    alignedmalloc.cc
    editcallbacks.cc
    main-cli.cc
    multilangmgr.cc
    options.cc
    paramsedited.cc
    pathutils.cc
    threadutils.cc
)

set(NONCLISOURCEFILES
    adjuster.cc
    alignedmalloc.cc
    aspectratios.cc
    batchqueue.cc
    batchqueuebuttonset.cc
    batchqueueentry.cc
    batchqueuepanel.cc
    batchtoolpanelcoord.cc
    bayerpreprocess.cc
    bayerprocess.cc
    bayerrawexposure.cc
    blackwhite.cc
    bqentryupdater.cc
    browserfilter.cc
    cacheimagedata.cc
    cachemanager.cc
    cacorrection.cc
    checkbox.cc
    chmixer.cc
    clipboard.cc
    coarsepanel.cc
    colorappearance.cc
    coloredbar.cc
    colortoning.cc
    colorpreview.cc
    controllines.cc
    controlspotpanel.cc
    coordinateadjuster.cc
    compressgamut.cc
    crop.cc
    crophandler.cc
    cropwindow.cc
    cursormanager.cc
    curveeditor.cc
    curveeditorgroup.cc
    darkframe.cc
    defringe.cc
    dehaze.cc
    diagonalcurveeditorsubgroup.cc
    dirbrowser.cc
    dirpyrdenoise.cc
    dirpyrequalizer.cc
    distortion.cc
    dynamicprofilepanel.cc
    editbuffer.cc
    editcallbacks.cc
    editorpanel.cc
    editwidgets.cc
    editwindow.cc
    epd.cc
    eventmapper.cc
    exiffiltersettings.cc
    exifpanel.cc
    exportpanel.cc
    externaleditorpreferences.cc
    extprog.cc
    fattaltonemap.cc
    filebrowser.cc
    filebrowserentry.cc
    filecatalog.cc
    filepanel.cc
    filethumbnailbuttonset.cc
    filmnegative.cc
    filmsimulation.cc
    filterpanel.cc
    flatcurveeditorsubgroup.cc
    flatfield.cc
    framing.cc
    gradient.cc
    guiutils.cc
    histogrampanel.cc
    history.cc
    hsvequalizer.cc
    iccprofilecreator.cc
    icmpanel.cc
    imagearea.cc
    imageareapanel.cc
    impulsedenoise.cc
    indclippedpanel.cc
    inspector.cc
    iptcpanel.cc
    labcurve.cc
    labgrid.cc
    lensgeom.cc
    lensprofile.cc
    localcontrast.cc
    locallab.cc
    locallabtools.cc
    locallabtools2.cc
    lockablecolorpicker.cc
    lwbutton.cc
    lwbuttonset.cc
    main.cc
    metadatapanel.cc
    multilangmgr.cc
    mycurve.cc
    mydiagonalcurve.cc
    myflatcurve.cc
    navigator.cc
    options.cc
    paramsedited.cc
    partialpastedlg.cc
    pathutils.cc
    pcvignette.cc
    pdsharpening.cc
    perspective.cc
    placesbrowser.cc
    popupbutton.cc
    popupcommon.cc
    popuptogglebutton.cc
    preferences.cc
    preprocess.cc
    preprocesswb.cc
    previewhandler.cc
    previewloader.cc
    previewmodepanel.cc
    previewwindow.cc
    profilepanel.cc
    profilestorecombobox.cc
    prsharpening.cc
    rawcacorrection.cc
    rawexposure.cc
    recentbrowser.cc
    renamedlg.cc
    resize.cc
    retinex.cc
    rgbcurves.cc
    rotate.cc
    rtappchooserdialog.cc
    rtimage.cc
    rtscalable.cc
    rtsurface.cc
    rtwindow.cc
    saveasdlg.cc
    saveformatpanel.cc
    sensorbayer.cc
    sensorxtrans.cc
    shadowshighlights.cc
    sharpenedge.cc
    sharpening.cc
    sharpenmicro.cc
    shcselector.cc
    softlight.cc
    soundman.cc
    splash.cc
    spot.cc
    threadutils.cc
    thresholdadjuster.cc
    thresholdselector.cc
    thumbbrowserbase.cc
    thumbbrowserentrybase.cc
    thumbimageupdater.cc
    thumbnail.cc
    tonecurve.cc
    toneequalizer.cc
    toolbar.cc
    toollocationpref.cc
    toolpanel.cc
    toolpanelcoord.cc
    vibrance.cc
    vignetting.cc
    wavelet.cc
    whitebalance.cc
    xtransprocess.cc
    xtransrawexposure.cc
    zoompanel.cc
)

if(APPLE)
    find_package(MacIntegration REQUIRED)
    # At the time of writing CMake has no module finder for gtkmacintegration so here we have it hard-coded, if installed via macports it should be in /opt/local/...
    set(EXTRA_LIB_RTGUI "${MacIntegration_LIBRARIES}")
    set(EXTRA_INCDIR "${EXTRA_INCDIR}" "${MacIntegration_INCLUDE_DIRS}")
endif()

if(WIN32)
    set(EXTRA_SRC_CLI myicon.rc)
    set(EXTRA_SRC_NONCLI myicon.rc)
    set(EXTRA_LIB_RTGUI winmm)
endif()

# Create new executables targets
add_executable(rth "${EXTRA_SRC_NONCLI}" "${NONCLISOURCEFILES}")
add_executable(rth-cli "${EXTRA_SRC_CLI}" "${CLISOURCEFILES}")

# Subdirectories that are not libraries themselves should be included
# like #include "your_subdirectory/header.h"
target_include_directories(rth PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(rth-cli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Add dependencies to executables targets
add_dependencies(rth UpdateInfo)
add_dependencies(rth-cli UpdateInfo)

# Create config.h which defines where data are stored
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/config.h")
# UpdateInfo and above creates new headers in build directory
target_include_directories(rth BEFORE PRIVATE ${CMAKE_BINARY_DIR}/rtgui)
target_include_directories(rth-cli BEFORE PRIVATE ${CMAKE_BINARY_DIR}/rtgui)

#Define a target specific definition to use in code
target_compile_definitions(rth PUBLIC GUIVERSION)
target_compile_definitions(rth-cli PUBLIC CLIVERSION)

# Set executables targets properties, i.e. output filename and compile flags
# for "Debug" builds, open a console in all cases for Windows version
if((WIN32) AND NOT(UPPER_CMAKE_BUILD_TYPE STREQUAL "DEBUG"))
    set_target_properties(rth PROPERTIES LINK_FLAGS "-mwindows")
endif()
set_target_properties(rth PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS}" OUTPUT_NAME rawtherapee)
set_target_properties(rth-cli PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS}" OUTPUT_NAME rawtherapee-cli)

target_include_directories(rth PRIVATE ${EXTRA_INCDIR})
target_include_directories(rth-cli PRIVATE ${EXTRA_INCDIR})

# Add linked libraries dependencies to executables targets
target_link_libraries(rth
    rtengine
    PkgConfig::GTKMM
    ${EXTRA_LIB_RTGUI}
    ${EXTRA_LIBDIR}
    ${TCMALLOC_LIBRARIES}
)

target_link_libraries(rth-cli
    rtengine
    PkgConfig::GTKMM
    ${EXTRA_LIB_RTGUI}
    ${EXTRA_LIBDIR}
    ${TCMALLOC_LIBRARIES}
)

if(USE_LIBCANBERRA)
    target_link_libraries(rth PkgConfig::CANBERRA)
endif()

# Install executables
install(TARGETS rth DESTINATION "${BINDIR}")
install(TARGETS rth-cli DESTINATION "${BINDIR}")
