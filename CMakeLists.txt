cmake_minimum_required(VERSION 3.5)

project(CS1023-SDF LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Sql Network)

if(ANDROID)
  add_library(Project SHARED
    main.cpp
    user.cpp
    user.h
    Book.cpp
    Book.h
    Discussion_Forum.cpp
    Discussion_Forum.h
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    homewindow.cpp
    homewindow.h
    homewindow.ui
    signupwindow.cpp
    signupwindow.h
    signupwindow.ui
    add_book_page.cpp
    add_book_page.h
    add_book_page.ui
    search_books.cpp
    search_books.h
    search_books.ui
    global_variables.cpp
    global_variables.h
    create_forum.cpp
    create_forum.h
    create_forum.ui
    find_forum.cpp
    find_forum.h
    find_forum.ui
    view_profile.cpp
    view_profile.h
    view_profile.ui
    server.cpp
    server.h
    chatclient.cpp
    chatclient.h
    chatclient.ui
    borrowed_books.cpp
    borrowed_books.h
    borrowed_books.ui
    lent_books.cpp
    lent_books.h
    lent_books.ui
    changepassword.cpp
    changepassword.h
    changepassword.ui
    find_friend.cpp
    find_friend.h
    find_friend.ui
    pending_book_req.cpp
    pending_book_req.h
    pending_book_req.ui
    pending_friend_req.cpp
    pending_friend_req.h
    pending_friend_req.ui
    pending_forum_req.cpp
    pending_forum_req.h
    pending_forum_req.ui
    yourfriends.cpp
    yourfriends.h
    yourfriends.ui
    yourforums.cpp
    yourforums.h
    yourforums.ui
  )
else()
  add_executable(Project
    main.cpp
    user.cpp
    user.h
    Book.cpp
    Book.h
    Discussion_Forum.cpp
    Discussion_Forum.h
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    homewindow.cpp
    homewindow.h
    homewindow.ui
    signupwindow.cpp
    signupwindow.h
    signupwindow.ui
    add_book_page.cpp
    add_book_page.h
    add_book_page.ui
    search_books.cpp
    search_books.h
    search_books.ui
    global_variables.cpp
    global_variables.h
    create_forum.cpp
    create_forum.h
    create_forum.ui
    find_forum.cpp
    find_forum.h
    find_forum.ui
    view_profile.cpp
    view_profile.h
    view_profile.ui
    server.cpp
    server.h
    chatclient.cpp
    chatclient.h
    chatclient.ui
    borrowed_books.cpp
    borrowed_books.h
    borrowed_books.ui
    lent_books.cpp
    lent_books.h
    lent_books.ui
    changepassword.cpp
    changepassword.h
    changepassword.ui
    find_friend.cpp
    find_friend.h
    find_friend.ui
    pending_book_req.cpp
    pending_book_req.h
    pending_book_req.ui
    pending_friend_req.cpp
    pending_friend_req.h
    pending_friend_req.ui
    pending_forum_req.cpp
    pending_forum_req.h
    pending_forum_req.ui
    yourfriends.cpp
    yourfriends.h
    yourfriends.ui
    yourforums.cpp
    yourforums.h
    yourforums.ui
  )
endif()

target_link_libraries(Project PRIVATE Qt5::Widgets)
target_link_libraries(Project PRIVATE Qt5::Core Qt5::Sql Qt5::Network)
