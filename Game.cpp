#include "Game.h"

//Static Functions

//Initializer Functions
void Game::initVariables()
{
    this->window = nullptr;
    this->fullscreen = false;
    this->dt = 0.f;
}

void Game::InitWindow()
{
	//Create SFML Window using options from window.ini file
    std::ifstream ifs("Config/window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();

    std::string title = "None";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    bool fullscreen = false;
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;
    
    if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;
    }
    ifs.close();

    this->fullscreen = fullscreen;
    this->windowSettings.antialiasingLevel = antialiasing_level;
    if(fullscreen)
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
    else
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{
    std::ifstream ifs("Config/supported_keys.ini");

    if (ifs.is_open()) {
        std::string key = "";
        int key_value = 0;
        while (ifs >> key >> key_value) {
            this->supportedKeys[key] = key_value;
        }
    }       
    ifs.close();
}

void Game::initStates()
{
    this->states.push_back(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

//Constructors/Destructors

Game::Game()
{    
    this->InitWindow();
    this->initKeys();
    this->initStates();
}

Game::~Game()
{
	delete this->window;    
    for (int i = 0; i < this->states.size(); i++)
    {
        delete this->states[i];
    }
    this->states.clear();
}

//Functions
void Game::endApplication()
{
    std::cout << "Ending App" << "\n";
}

void Game::UpdateDT()
{
    //Update the dt var with the time it takes to update and render 1 frame
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::UpdateSFMLEvents()
{
    //Event polling
    while (this->window->pollEvent(this->sfEvent)) {
        switch (this->sfEvent.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        }
    }
   
}

void Game::Update()
{
    this->UpdateSFMLEvents();

    if (!this->states.empty()) {
        this->states.back()->Update(this->dt);

        if (this->states.back()->getQuit()) {
            
            this->states.back()->endState();
            this->states.pop_back();
        }
    }
    //Application End
    else {
        this->endApplication();
        this->window->close();
    }
}

void Game::Render()
{
    this->window->clear();

    //Render items
    if (!this->states.empty())
        this->states.back()->Render();

    this->window->display();
}

void Game::Run()
{
    //Game loop
    while (this->window->isOpen()) {
        this->UpdateDT();
        this->Update();
        this->Render();
    }
}
