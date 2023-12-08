<<<<<<< HEAD
# Adafruit GFX Library
# https://github.com/adafruit/Adafruit-GFX-Library
# BSD License

cmake_minimum_required(VERSION 3.5)

idf_component_register(SRCS "Adafruit_GFX.cpp" "Adafruit_GrayOLED.cpp" "Adafruit_SPITFT.cpp" "glcdfont.c"
                       INCLUDE_DIRS "."
                       REQUIRES arduino Adafruit_BusIO)

project(Adafruit-GFX-Library)
=======
# Adafruit GFX Library
# https://github.com/adafruit/Adafruit-GFX-Library
# BSD License

cmake_minimum_required(VERSION 3.5)

idf_component_register(SRCS "Adafruit_GFX.cpp" "Adafruit_GrayOLED.cpp" "Adafruit_SPITFT.cpp" "glcdfont.c"
                       INCLUDE_DIRS "."
                       REQUIRES arduino Adafruit_BusIO)

project(Adafruit-GFX-Library)
>>>>>>> e6874f604529d3bf2dcc39e924c37ec67d072f9c
