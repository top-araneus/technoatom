#ifndef DIALOGS_H
#define DIALOGS_H

#include "refpoint.h"
#include "buttonfactory.h"
class DialogWindow
{
  public:
    DialogWindow(LinearVector<int> constraints, LinearVector<int> coords);
    ~DialogWindow();
    void Draw();
    Button* AddButton(LinearVector<int> constraints, LinearVector<int> coords, std::string caption);
    const sf::RectangleShape& GetForm() {
      return form_;
    }
    Array<Button*>&     GetButtons() {
      return buttons_;
    }
    Array<sf::Text*>&   GetTexts() {
      return texts_;
    }
    const bool                GetVisible() {
      return is_visible_;
    }
    const void                SetVisible(bool value) {
      is_visible_ = value;
    }
    void Close();
    LinearVector<int> constraints_;
    LinearVector<int> coords_;
  protected:
    bool is_visible_;
    sf::Color background_color_;
    Array<Button*> buttons_;  //get
    Array<sf::Text*> texts_;  //get
    sf::RectangleShape form_; //get
};

DialogWindow::DialogWindow(LinearVector<int> constraints, LinearVector<int> coords)
{
  constraints_ = constraints;
  coords_ = coords;
  background_color_ = kDialogWindowColor;
  form_ = sf::RectangleShape(constraints_);
  form_.setPosition(coords);
  form_.setFillColor(background_color_);
  buttons_ = Array<Button*>(kDialogElemsMaxNumber);
  texts_ = Array<sf::Text*>(kDialogElemsMaxNumber);
  for (int i = 0; i < 20; ++i)
  {
    buttons_[i] = nullptr;
    texts_[i] = nullptr;
  }
  is_visible_ = true;
  buttons_[0] = ButtonFactory::GetExitButton(constraints, coords);
 buttons_[0]->OnClick.Connect(this, &DialogWindow::Close);
}

void DialogWindow::Close()
{
  is_visible_ = false;
}

Button* DialogWindow::AddButton(LinearVector<int> constraints, LinearVector<int> coords, std::string caption)
{
  for (int i = 0; i<kDialogElemsMaxNumber; ++i)
  {
    if (buttons_[i] == nullptr)
    {
      LinearVector<int> button_coords;
      button_coords.x_ = coords_.x_ + coords.x_;
      button_coords.y_ = coords_.y_ + coords.y_;
      buttons_[i] = ButtonFactory::GetButton(constraints, button_coords, caption);
      return buttons_[i];
    }
  }
  return nullptr;
}

void DialogWindow::Draw()
{
  /*
  if (is_visible_)
  {
    form_.draw();
    for (int i = 0; i<kDialogElemsMaxNumber; ++i)
    {
      if (buttons_[i] != nullptr)
      {
        if (buttons_[i]->GetVisible())
          buttons_[i]->Draw();
      }
    }
  }
  */
}

#endif // DIALOGS_H
