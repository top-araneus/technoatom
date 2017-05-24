#ifndef BUTTONS_H
#define BUTTONS_H

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
    bool enabled_;
    bool visible_;
};

#endif // BUTTONS_H
