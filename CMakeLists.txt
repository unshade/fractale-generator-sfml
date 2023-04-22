cmake_minimum_required(VERSION 3.25)
project(fractale_generator_sfml)

set(CMAKE_CXX_STANDARD 17)

# Spécifiez le chemin d'installation de SFML
set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.5.1_2/lib/cmake/SFML")

# Trouvez les packages SFML nécessaires (system, window, graphics, network, audio)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(fractale_generator_sfml main.cpp)

# Liez les bibliothèques SFML à l'exécutable
target_link_libraries(fractale_generator_sfml sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# Copier le fichier julia_set.shader dans le répertoire de construction
add_custom_target(copy_shader ALL
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/julia_set.glsl
        $<TARGET_FILE_DIR:fractale_generator_sfml>/julia_set.glsl
        DEPENDS ${CMAKE_SOURCE_DIR}/julia_set.glsl)

# Ajouter une dépendance à l'exécutable pour copier le shader lorsque le fichier est modifié
add_dependencies(fractale_generator_sfml copy_shader)
