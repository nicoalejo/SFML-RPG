#include "MainMenuState.h"

//Initializar Functions
void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.jpg")) {
		throw "ERROR::MAIN MENU STATE::FAILED TO LOAD BACKGROUND TEXTURE";
	}
	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Enchanted-Land.otf")) {
		throw("ERROR::MAINMENUSTATE::Could not load font");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();

}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(150.f, 100.f, 300.f, 100.f,
		&this->font, "New Game", 50,
		sf::Color(224, 122, 49, 255), sf::Color(224, 122, 49, 255), sf::Color(224, 122, 49, 200),
		sf::Color(18, 135, 148, 200), sf::Color(64, 188, 199, 255), sf::Color(18, 135, 148, 200));

	this->buttons["SETTINGS"] = new Button(150, 300, 300, 100,
		&this->font, "Settings", 50,
		sf::Color(224, 122, 49, 255), sf::Color(224, 122, 49, 255), sf::Color(224, 122, 49, 200),
		sf::Color(18, 135, 148, 200), sf::Color(64, 188, 199, 255), sf::Color(18, 135, 148, 200));

	this->buttons["EDITOR_STATE"] = new Button(150, 500, 300, 100,
		&this->font, "Editor", 50,
		sf::Color(224, 122, 49, 255), sf::Color(224, 122, 49, 255), sf::Color(224, 122, 49, 200),
		sf::Color(18, 135, 148, 200), sf::Color(64, 188, 199, 255), sf::Color(18, 135, 148, 200));

	this->buttons["EXIT_STATE"] = new Button(150, 700, 300, 100,
		&this->font, "Quit", 50,
		sf::Color(224, 122, 49, 255), sf::Color(224, 122, 49, 255), sf::Color(224, 122, 49, 200),
		sf::Color(18, 135, 148, 200), sf::Color(64, 188, 199, 255), sf::Color(18, 135, 148, 200));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();	
}

MainMenuState::~MainMenuState()
{	
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

void MainMenuState::updateInput(const float& dt)
{	
		
}

void MainMenuState::updateButtons()
{
	//Updates all the buttons + handles functionality
	for (auto& it : this->buttons)
	{
		it.second->Update(this->mousePosView);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed()) {
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}
	
	//Editor State
	if (this->buttons["EDITOR_STATE"]->isPressed()) {
		this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
	}	

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed()) {
		this->endState();
	}
}

void MainMenuState::Update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	this->updateButtons();	
}	

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->Render(target);
	}
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);	

	this->renderButtons(target);

	//REMOVE LATER
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y -50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(36);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}

