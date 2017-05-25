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
#endif // DIALOGMANAGER_H
