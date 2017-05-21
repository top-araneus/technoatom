#ifndef DIALOGS_H
#define DIALOGS_H

#include "refpoint.h"

class DialogWindow
{
  public:
    DialogWindow();
    ~DialogWindow();
    void Draw();
  protected:
    class Button
    {
    public:
        Button();
        ~Button();
        LinearVector<int> constraints_;
        LinearVector<int> coords_;
        sf::Color background_color_;
        sf::Text text_;
        bool pressed_;
        void OnClick();
    };
    bool is_visible_;
    LinearVector<int> constraints_;
    LinearVector<int> ref_coords_;
    sf::Color background_color_;
    Array<Button*> buttons_;
    Array<sf::Text*> texts_;
    sf::RectangleShape form_;
    ReferenceFrame frame_;
};

DialogWindow::DialogWindow(ReferenceFrame& frame, LinearVector<int> constraints, LinearVector<int> ref_coords)
{
  frame_ = frame;
  constraints_ = constraints;
  ref_coords_ = ref_coords;
  background_color_ = kDialogWindowColor;
  form_ = sf::RectangleShape(constraints_);
  form_.setPosition(ref_coords_ + frame_.GetCoords());
  form_.setFillColor(background_color_);
  buttons_ = Array<Button*>(20);
  texts_ = Array<sf::Text*>(20);
  for (int i = 0; i < 20; ++i)
  {
    buttons_[i] = nullptr;
    texts_[i] = nullptr;
  }

}
#endif // DIALOGS_H
