#ifndef BASE_OVERWORLD_OBJECT_HPP
#define BASE_OVERWORLD_OBJECT_HPP

#include "BaseGameObject.hpp"

class BaseOverworldObject : public BaseGameObject {
public:
	BaseOverworldObject(const std::string &, int, int, int, int);
	virtual ~BaseOverworldObject() override;

	bool isVisible() const;
	int getMapX() const;
	int getMapY() const;
	int getPrevMapX() const;
	int getPrevMapY() const;
	void setMapX(int);
	void setMapY(int);
	void setVisible(bool);

private:
	int mapX, mapY;
	int prevMapX, prevMapY;
	bool visible;
};

#endif