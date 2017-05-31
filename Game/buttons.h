#ifndef BUTTONS_H
#define BUTTONS_H
#include "constants.h"
class Button
{
public:
    Button(LinearVector<int> constraints, LinearVector<int> coords, std::string caption);
    ~Button();
    LinearVector<int> constraints_;
    LinearVector<int> coords_;
    sf::RectangleShape form_; //get
    sf::Color background_color_;
    sf::Text text_; //get
    std::string caption_;
    sf::Font font_;
    Delegate OnClick;
    void Draw();
    bool GetVisible() {
      return visible_;
    }
    void                      SetVisible(bool value) {
    visible_ = value;
    }
    const sf::RectangleShape& GetForm() {
      return form_;
    }
    const sf::Text& GetText() {
      return text_;
    }
    bool pressed_;
    void SetCoords(LinearVector<int> coords)
    {
      print("new button coords /# /# \n", coords.x_, coords.y_);
      coords_ = coords;
      form_.setPosition(coords_);
      LinearVector<int> text_coords;
      text_coords.x_ = coords_.x_ + constraints_.x_ / 3;
      text_coords.y_ = coords_.y_ + constraints_.y_ / 3;
      text_.setPosition(text_coords);
    }
private:
    bool visible_; //get, set
    bool enabled_;
};

Button::Button(LinearVector<int> constraints, LinearVector<int> coords, std::string caption)
{
  constraints_ = constraints;
  coords_ = coords;
  background_color_ = kButtonColor;
  visible_ = true;
  enabled_ = true;
  pressed_ = false;
  form_ = sf::RectangleShape(constraints_);
  form_.setFillColor(background_color_);
  form_.setPosition(coords_);
  caption_ = caption;
  font_.loadFromFile(kFontPath);
  text_.setFont(font_);
  text_ = sf::Text(caption_, font_, 10);
  text_.setColor(kTextColor);
  LinearVector<int> text_coords;
  text_coords.x_ = coords_.x_ + constraints_.x_ / 3;
  text_coords.y_ = coords_.y_ + constraints_.y_ / 3;
  text_.setPosition(text_coords);
}



#endif // BUTTONS_H
