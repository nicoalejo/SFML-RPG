#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800, 600), "First Window", Style::Titlebar | Style::Close);
    Event ev;
    
    //Game loop
    while (window.isOpen()) {
        //Event polling
        while (window.pollEvent(ev)) {
            switch (ev.type)
            {
            case Event::Closed: 
                window.close();   
                break;
            case Event::KeyPressed:
                if(ev.key.code == Keyboard::Escape)
                    window.close();
                break;
            }
        }
        //Update


        //Render
        window.clear(Color::Blue); //clear old frame

        //Draw your game

        window.display(); //Tell app that window is done drawing
    }

    

    //End of application
    return 0;
}