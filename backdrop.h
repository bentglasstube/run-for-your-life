#pragma once

#include <string>

class Graphics;

class Backdrop {

  public:

    Backdrop(const std::string& file);
    virtual ~Backdrop() {}

    void draw(Graphics& graphics);
    virtual void update() {}

  private:

    std::string file;

};
