CC = g++
FILES = ../src/Main.cpp ../src/game/Gahoodmon.cpp ../src/game/Window.cpp ../src/util/Util.cpp ../src/util/Constants.cpp ../src/util/Timer.cpp ../src/util/FileUtil.cpp ../src/object/Sprite.cpp ../src/util/ImageLoader.cpp ../src/screen/BaseScreen.cpp ../src/object/Image.cpp ../src/screen/IntroScreen.cpp ../src/animation/Animator.cpp ../src/animation/BaseAnimation.cpp ../src/animation/FadeAnimation.cpp ../src/screen/MainMenuScreen.cpp ../src/screen/MapScreen.cpp ../src/map/Tile.cpp ../src/util/XMLParser.cpp ../src/util/MapLoader.cpp ../src/util/DisplayUtil.cpp ../src/map/Map.cpp ../src/map/Tileset.cpp
FLAGS = -std=c++11
LIBS = -lSDL2 -lSDL2_image
OUT = game.out
GAME:
	$(CC) $(FILES) -o $(OUT) $(FLAGS) $(LIBS)
