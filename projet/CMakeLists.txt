cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_VERBOSE_MAKEFILE ON)
# La raison pour laquelle on fait une variable d'environnement VCPKG_ROOT.
if (DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

# Le nom du projet.
project(Chess)

# Tous les package Vcpkg. Pour savoir quoi mettre, on fait "vcpkg install <le package>", puis on met ce qu'ils disent de mettre dans le CMakeLists.
find_package(cppitertools CONFIG REQUIRED)  # On pourrait prendre le cppitertools de vcpkg au lieu de celui fourni dans include/
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
find_package(GTest CONFIG REQUIRED)
qt_standard_project_setup()
enable_testing()

# On met les fichiers sources (incluant les entêtes)
set(ALL_FILES
    "main.cpp"
    "model/board.cpp"
    "model/pieces/king.cpp"
    "model/pieces/pawn.cpp"
    "model/pieces/piece.cpp"
    "model/pieces/rook.cpp"
    "view/maingui.cpp"
    "view/squaregui.cpp"
    "bibliotheque_cours/bibliotheque_cours.cpp"
    "bibliotheque_cours/verification_allocation.cpp"

    "tests/testboard.cpp"
    "tests/testpiece.cpp"
)

add_executable(${PROJECT_NAME} ${ALL_FILES})

# Les flags de compilation. Ceux-ci reproduisent un peu le comportement de MSVC avec /W4.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -fsigned-char -Wall -Wextra -Wpedantic -Woverloaded-virtual -Wno-unknown-pragmas -Wno-enum-compare --coverage")

# On ajoute le dossier include/ fourni, comme des fichiers d'inclusion du système.
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE "include")

# Si on trouve gcov, on fait un cible avec nom ..._couveture pour exécuter gcov et obtenir la couverture de code.
find_program(GCOV_PATH gcov)
if (GCOV_PATH)
	add_custom_target(${PROJECT_NAME}_couverture
		# Vous devez exécuter le programme avant de "build" cette cible, ou décommenter la ligne suivante qui l'exécute mais ne fonctionne pas si le programme a besoin d'interagir avec l'usager:
		# COMMAND ${PROJECT_NAME}
	 
		# Analyse le fichier de couverture:
        COMMAND ${GCOV_PATH} -s "${Chess_SOURCE_DIR}" -r -f -m "${PROJECT_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}.dir/source/*.gcda"

		WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
		DEPENDS ${PROJECT_NAME}
	)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets cppitertools::cppitertools GTest::gtest GTest::gtest_main)

include(GoogleTest)
gTest_discover_tests(${PROJECT_NAME})
