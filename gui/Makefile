##
## EPITECH PROJECT, 2024
## B-YEP-400-STG-4-1-zappy-augustin.grosnon
## File description:
## Makefile
##

SRC	=	Src/main.cpp \
		Src/Wrapper/Graphics/Shape/Drawable.cpp \
		Src/Wrapper/Graphics/Shape/Transformable.cpp \
		Src/Wrapper/Graphics/Shape/Shape.cpp \
		Src/Wrapper/Graphics/Shape/VisualElement.cpp \
		Src/Wrapper/Graphics/Shape/RectangleShape.cpp \
		Src/Wrapper/Graphics/Shape/CircleShape.cpp \
		Src/Wrapper/Graphics/RenderWindow.cpp \
		Src/Wrapper/Graphics/TextureManager.cpp \
		Src/Wrapper/Graphics/Sprite.cpp \
		Src/Wrapper/Graphics/Notification.cpp \
		Src/Wrapper/Graphics/Text.cpp \
		Src/Wrapper/Graphics/Font.cpp \
		Src/Wrapper/Graphics/Transform/Transform.cpp \
		Src/Wrapper/Graphics/Transform/Movements.cpp \
		Src/Wrapper/Graphics/Scoped.cpp \
		Src/Wrapper/Graphics/Camera/Camera2.cpp \
		Src/Wrapper/Graphics/Camera/Camera3.cpp \
		Src/Wrapper/Graphics/Inventory.cpp \
		Src/Wrapper/Graphics/Player.cpp \
		Src/Wrapper/Graphics/Tile.cpp \
		Src/Wrapper/Graphics/TilesWrapper.cpp \
		Src/Wrapper/Graphics/Item.cpp \
		Src/Wrapper/Graphics/Objects/Grid.cpp \
		Src/Wrapper/Graphics/Objects/Object.cpp \
		Src/Wrapper/Graphics/Objects/Cube.cpp \
		Src/Wrapper/Graphics/Objects/Model3.cpp \
		Src/Wrapper/Graphics/Objects/Sphere.cpp \
		Src/Wrapper/Graphics/Objects/Torus.cpp \
		Src/Wrapper/Graphics/InputText.cpp \
		Src/Wrapper/Graphics/SplashScreenManager.cpp \
		Src/Wrapper/Graphics/Splash.cpp \
		Src/Wrapper/Graphics/Button.cpp \
		Src/Wrapper/Window/Keyboard.cpp \
		Src/Wrapper/Window/Mouse.cpp \
 		Src/Wrapper/Window/Clickable/Clickable.cpp \
		Src/Wrapper/System/Clock.cpp \
		Src/Wrapper/System/Time.cpp \
		Src/Wrapper/Audio/AudioSource.cpp \
		Src/Wrapper/Audio/SoundSource.cpp \
		Src/Wrapper/Audio/MusicSource.cpp \
		Src/Wrapper/Audio/AudioManager.cpp \
		Src/Wrapper/Scene/AScene.cpp \
		Src/Wrapper/ArgumentParser.cpp	\
		Src/Scene/SceneManager.cpp \
		Src/Scene/MainMenu.cpp \
		Src/Scene/Game.cpp \
		Src/Scene/Pause.cpp \
		Src/Scene/Setting/MainSetting.cpp \
		Src/Scene/Setting/MiscellaneousSetting.cpp \
		Src/Scene/Setting/KeyboardSetting.cpp \
		Src/Scene/Setting/ResolutionSetting.cpp \
		Src/Scene/Setting/SoundSetting.cpp \
		Src/Scene/Setting/SettingsValue.cpp \
		Src/Network/NetworkManager.cpp \
		Src/Vector.cpp \
		Src/Rainbow.cpp \
		Src/Wrapper/Graphics/Space/Star.cpp \
		Src/Wrapper/Graphics/Space/StellarObject.cpp \
		Src/Wrapper/Graphics/Space/Sky.cpp \
		Src/Wrapper/Graphics/Space/Planet.cpp \
		Src/Egg.cpp

OBJ	= $(patsubst Src/%.cpp, build/%.o, $(SRC))
DIRS	=	$(sort $(dir $(OBJ)))

NAME	=	zappy_gui

CPPFLAGS	=	-g -std=c++20 -O3 -flto
INCLUDES	+=	-I./Includes
INCLUDES	+=	-I./Includes/Objects
INCLUDES	+=	-I./Includes/Raylib
INCLUDES	+=	-I./Includes/Scene
INCLUDES	+=	-I./Includes/SoundManager
INCLUDES	+=	-I./Includes/Wrapper
INCLUDES	+=	-I./Includes/Wrapper/Graphics
INCLUDES	+=	-I./Includes/Wrapper/Graphics/Shape
INCLUDES	+=	-I./Includes/Wrapper/Graphics/Transform
INCLUDES	+=	-I./Includes/Wrapper/Graphics/Objects
INCLUDES	+=	-I./Includes/Wrapper/Graphics/Camera
INCLUDES	+=	-I./Includes/Wrapper/Window
INCLUDES	+=	-I./Includes/Wrapper/Window/Clickable
INCLUDES	+=	-I./Includes/Wrapper/System
INCLUDES	+=	-I./Includes/Wrapper/Audio
INCLUDES	+=	-I./Includes/Wrapper/Scene
INCLUDES	+=	-I./Includes/Factory
INCLUDES	+=	-I./Includes/Scene/Setting
INCLUDES	+=	-I./Includes/Network
INCLUDES	+=	-I./Includes/Wrapper/Graphics/Space

RAYLIB_FLAGS	=	-lraylib -Wall -Wextra

all: build $(NAME)

build:
	mkdir -p $(DIRS)

$(NAME):	$(OBJ)
	g++ $^ -o $@ $(CPPFLAGS) $(INCLUDES) $(RAYLIB_FLAGS)
	mv ./$(NAME) ..
	cp -r ./Assets ..

build/%.o:	Src/%.cpp
	g++ -c $< -o $@ $(CPPFLAGS) $(INCLUDES) $(RAYLIB_FLAGS)

clean:
	rm -rf build

fclean: clean
	rm -rf ../Assets
	rm -rf ../$(NAME)
	rm -f ../currentScene.png
	rm -f ../MenuBackground.png

re: fclean all

cppclean:
	cppclean $(INCLUDES) .

.PHONY: all clean fclean re cppclean
