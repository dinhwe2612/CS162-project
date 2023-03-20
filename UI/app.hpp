#include <iostream>

class App
{
public: 
    App(int windowWidth, int windowHeight, int fps, std::string title);
    ~App();

    bool AppShouldClose() const;

    void Tick();

private:
    void Update();
    void Draw();
};