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
    sf::Text* AddText(int text_size, LinearVector<int> coords, std::string caption);
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
    void SetCoords(LinearVector<int> delta, LinearVector<int> coords);

    //! REMOVE AFTER TEST !
    void TestFunc();
    int ctr_ = 0;
    //!                   !

    LinearVector<int> constraints_;
    LinearVector<int> coords_;
  protected:
    bool is_visible_;
    sf::Color background_color_;
    sf::Font font_;
    Array<Button*> buttons_;  //get
    Array<sf::Text*> texts_;  //get
    sf::RectangleShape form_; //get
};

DialogWindow::DialogWindow(LinearVector<int> constraints, LinearVector<int> coords)
{
  constraints_ = constraints;
  coords_ = coords;
  font_ = sf::Font();
  font_.loadFromFile(kFontPath);
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
 //AddText(10, LinearVector<int>(10, 50), "");
}

void DialogWindow::Close()
{
  is_visible_ = false;
}

void DialogWindow::TestFunc()
{
  texts_[0]->setString(std::to_string(++ctr_));
}

void DialogWindow::SetCoords(LinearVector<int> delta, LinearVector<int> coords)
{
  coords_ = coords;
  form_.setPosition(coords);
  for (int j = 0; j<kDialogElemsMaxNumber; ++j)
  {
    if (buttons_[j] != nullptr)
    {
      Button* button = buttons_[j];
      button->coords_.x_ += delta.x_;
      button->coords_.y_ += delta.y_;
      button->SetCoords(button->coords_);
      //button->SetCoords(button->coords_);
      //print("Clicked to /# /#, window /# button /# on /# /# with constraints /# /#\n", x,y,i,j,button_x, button_y, button_width, button_height);
    }
    else break;
  }
  for (int j = 0; j<kDialogElemsMaxNumber; ++j)
  {
    if (texts_[j] != nullptr)
    {
      sf::Text* text = texts_[j];
      text->setPosition(text->getPosition().x + delta.x_, text->getPosition().y + delta.y_);
    }
    else break;
  }
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

sf::Text* DialogWindow::AddText(int text_size, LinearVector<int> coords, std::string caption)
{
  for (int i = 0; i<kDialogElemsMaxNumber; ++i)
  {
    if (texts_[i] == nullptr)
    {
      LinearVector<int> text_coords;
      text_coords.x_ = coords_.x_ + coords.x_;
      text_coords.y_ = coords_.y_ + coords.y_;
      texts_[i] = new sf::Text(sf::String(caption), font_, text_size);
      texts_[i]->setPosition(text_coords);
      return texts_[i];
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
