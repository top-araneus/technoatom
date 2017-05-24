#ifndef DIALOGS_H
#define DIALOGS_H

#include "refpoint.h"
#include "buttonfactory.h"
class DialogWindow
{
  public:
    DialogWindow(LinearVector<int> constraints, LinearVector<int> ref_coords);
    ~DialogWindow();
    void Draw();
  protected:
    bool is_visible_;
    LinearVector<int> constraints_;
    LinearVector<int> ref_coords_;
    sf::Color background_color_;
    Array<Button*> buttons_;
    Array<sf::Text*> texts_;
    sf::RectangleShape form_;
};

DialogWindow::DialogWindow(LinearVector<int> constraints, LinearVector<int> ref_coords)
{
  constraints_ = constraints;
  ref_coords_ = ref_coords;
  background_color_ = kDialogWindowColor;
  form_ = sf::RectangleShape(constraints_);
  form_.setPosition(frame_.GetCoords());
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
