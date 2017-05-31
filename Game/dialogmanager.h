#ifndef DIALOGMANAGER_H
#define DIALOGMANAGER_H

#include "dialogfactory.h"

class DialogManager {
private:
  Array<DialogWindow*> dialogs_;
  RenderWindow* window_;
public:
  Array<DialogWindow*>& GetDialogs() {
    return dialogs_;
  }
  DialogManager(RenderWindow* window);
  void OnClick(LinearVector<int> coords);
  void DrawDialogs();
  DialogWindow* AddDialog(LinearVector<int> constraints, LinearVector<int> coords);
  bool ManageClicks(LinearVector<int> coords, bool released);
  bool ManageMoves(LinearVector<int> coords, LinearVector<int> moved);
};

DialogManager::DialogManager(RenderWindow* window)
{
  window_ = window;
  dialogs_ = Array<DialogWindow*>(kDialogsMaxNumber);
  for (int i = 0; i<kDialogsMaxNumber; ++i)
  {
    dialogs_[i] = nullptr;
  }
}

DialogWindow* DialogManager::AddDialog(LinearVector<int> constraints, LinearVector<int> coords)
{
  for (int i = 0; i<kDialogsMaxNumber; ++i)
  {
    if (dialogs_[i] == nullptr)
    {
      dialogs_[i] = DialogFactory::GetDialogWindow(constraints, coords);
      return dialogs_[i];
    }
  }
  return nullptr;
}

void DialogManager::DrawDialogs()
{
  for (int i = 0; i<kDialogsMaxNumber; ++i)
  {
    if (dialogs_[i] != nullptr)
    {
      if (dialogs_[i]->GetVisible())
      {
        Array<Button*> buttons_ = dialogs_[i]->GetButtons();
        Array<sf::Text*> texts = dialogs_[i]->GetTexts();
        sf::RectangleShape form = dialogs_[i]->GetForm();
        window_->draw(form);
        for (int j = 0; j<kDialogElemsMaxNumber; ++j)
        {
          if (texts[j] != nullptr)
          {
            window_->draw(*(texts[j]));
          }
        }
        for (int j = 0; j<kDialogElemsMaxNumber; ++j)
        {
          if (buttons_[j] != nullptr)
          {
            if (buttons_[j]->GetVisible())
            {
              window_->draw(buttons_[j]->GetForm());
              window_->draw(buttons_[j]->GetText());
            }
          }
        }
      }
    }
  }
}


bool DialogManager::ManageMoves(LinearVector<int> coords, LinearVector<int> moved = LinearVector<int>(0,0))
{
  for (int i = 0; i<kDialogsMaxNumber; ++i)
  {
    if (dialogs_[i] != nullptr)
    {
      DialogWindow* dialog = dialogs_[i];
      if ((coords.x_ > dialog->coords_.x_ && coords.y_ > dialog->coords_.y_) && (coords.x_ < (dialog->coords_.x_ + dialog->constraints_.x_) && coords.y_ < (dialog->coords_.y_ + 100)))
      {
        dialog->coords_.x_ += moved.x_ - coords.x_;
        dialog->coords_.y_ += moved.y_ - coords.y_;
        dialog->SetCoords(moved-coords,  dialog->coords_);

      }
    }
    else break;
  }
  return false;
}

bool DialogManager::ManageClicks(LinearVector<int> coords, bool released)
{
  for (int i = 0; i<kDialogsMaxNumber; ++i)
  {
    if (dialogs_[i] != nullptr)
    {
      DialogWindow* dialog = dialogs_[i];
      if ((coords.x_ > dialog->coords_.x_ && coords.y_ > dialog->coords_.y_)
          && (coords.x_ < (dialog->coords_.x_ + dialog->constraints_.x_) && coords.y_ < (dialog->coords_.y_ + dialog->constraints_.y_)))
      {
        for (int j = 0; j<kDialogElemsMaxNumber; ++j)
        {
          if (dialog->GetButtons()[j] != nullptr)
          {
            Button* button = dialog->GetButtons()[j];
            int x = coords.x_;
            int y = coords.y_;
            int button_x = button->coords_.x_;
            int button_y = button->coords_.y_;
            int button_width = button->constraints_.x_;
            int button_height = button->constraints_.y_;
            //print("Clicked to /# /#, window /# button /# on /# /# with constraints /# /#\n", x,y,i,j,button_x, button_y, button_width, button_height);
            if (dialogs_[i]->GetVisible() && (x > button_x && x < (button_x + button_width)) && (y > button_y && y < (button_y + button_height)))
            {
              if (released)
              {
                if (button->pressed_)
                {
                  button->pressed_ = false;
                  button->OnClick();
                  return true;
                }
              }
              else
              {
                button->pressed_ = true;
                return true;
              }
            }
          }
        }
      }
    }
    else break;
  }
  return false;
}

#endif // DIALOGMANAGER_H
