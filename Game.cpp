#include "Game.h"

//Static Functions

//Initializer Functions
void Game::InitWindow()
{
	//Create SFML Window using options from window.ini file
    std::ifstream ifs("Config/window.ini");
    std::string title = "None";
    sf::VideoMode window_bounds(1920, 1080);
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    
    if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
    }
    ifs.close();

    this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close);
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

    //Debug Remove
    for (auto i: this->supportedKeys)
    {
        std::cout << i.first << " " << i.second << "\n";
    }
}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
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

    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
        
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
        this->states.top()->Update(this->dt);

        if (this->states.top()->getQuit()) {
            
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
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
        this->states.top()->Render();

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
