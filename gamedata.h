#ifndef GAMEDATA__H
#define GAMEDATA__H
#include <string>
#include <map>
#include "vector2f.h"
#include "parseXML.h"

class Gamedata {
public:
  static Gamedata& getInstance();
  ~Gamedata();
  void displayData() const;

  bool getXmlBool(const std::string&) const;
  const std::string& getXmlStr(const std::string&) const;
  float getXmlFloat(const std::string&) const;
  int getXmlInt(const std::string&) const;
  float getRandInRange(int min, int max) const;
  float getRandFloat(float min, float max) const;
  bool  checkTag(const std::string&)const;
  int getMouseX() const { return mouseX; }
  int getMouseY() const { return mouseY; }
  bool getRightKey() const { return rightKey; }
  bool getLeftKey() const { return leftKey; }
  void updateMouse(int x, int y) { mouseX = x; mouseY = y; }
  void updateLeft(bool setLeft) { leftKey = setLeft; }
  void updateRight(bool setRight) { rightKey = setRight; }
  static float clamp(const float, const float, const float);

private:
  ParseXML parser;
  const map<std::string, std::string> gameData;
  int mouseX, mouseY;
  bool rightKey, leftKey;

  Gamedata(const std::string& fn = "xmlSpec/game.xml");
  Gamedata(const Gamedata&);
  Gamedata& operator=(const Gamedata&);
};
#endif
