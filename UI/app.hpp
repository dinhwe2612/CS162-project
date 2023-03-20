#include <iostream>

class App
{
public: 
    App(int windowWidth, int windowHeight, int fps, std::string title);
    ~App();

    bool AppShouldClose() const;

    void Tick();

private:
    int windowWidth;
    int windowHeight;
    void Update();
    void Draw();
};