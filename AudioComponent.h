#pragma once
#include <SFML/Audio.hpp>
#include <string>

class AudioComponent
{
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
public:
	AudioComponent(const std::string& audio_location);
	virtual ~AudioComponent();

	//Functions
	const sf::Sound getSound();

	void playSound();
	void pauseSound();
	void stopSound();
};

