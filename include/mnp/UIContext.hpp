
class BaseUIContext : public InputContext {
    bool focusFlag;
public:
    // Used by ui to re-order rendering
    // Will reset focus state when called
    bool getFocus();
    bool wantsFocus(sf::Event *event);
    virtual bool wantsFocusImpl(sf::Event *event) = 0;

};


class UIClickableContext : public BaseUIContext {

public:
    UIClickableContext();
    ~UIClickableContext();

    Rectangle m_MyRect;
    bool clicked;

    void setRect(Rectangle r);

    bool handleInput(sf::Event *event);

    void update(sf::Time deltaTime);

    bool wantsFocusImpl(sf::Event *event);
};


class BlankContext : public BaseUIContext {
public:
    bool handleInput(sf::Event *event);
    void update(sf::Time deltaTime);

    bool wantsFocusImpl(sf::Event *event);
};
/*

class UITextInputContext : public BaseUiContext {

public:
    UITextInputContext();
    ~UITextInputContext();

    bool inFocus;

    std::list<sf::Keyboard::Key*> inputKeys;

    void update(sf::Time deltaTime);
    bool handleInput(sf::Event *event);
    bool wantsFocusImpl(sf::Event *event);

    virtual bool checkEnter(sf::Event *event) = 0;
    virtual int checkExit(sf::Event *event) = 0;
};
*/
