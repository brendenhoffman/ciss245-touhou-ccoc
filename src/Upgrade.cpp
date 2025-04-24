// Brenden Hoffman
// p01
// Upgrade.cpp
#include "Upgrade.h"

Upgrade::Upgrade(int x, int y, UpgradeType type)
  : x(x), y(y), size(16), speed(1.5f), type(type) {}

void Upgrade::update() {
  x -= speed;
}

void Upgrade::draw(Surface& surface) const {
  Color color;
  switch (type) {
    case UPG_FIRERATE: color = YELLOW; break;
    case UPG_LIFE:     color = GREEN;  break;
    case UPG_TRIPLE:   color = CYAN;   break;
  }
  surface.put_circle(x + size / 2, y + size / 2, size / 2, color);
}

bool Upgrade::isOffScreen() const {
  return x + size < 0;
}
