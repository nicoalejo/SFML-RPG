#include "AudioComponent.h"

AudioComponent::AudioComponent(const std::string& audio_location)
{
	if (!this->buffer.loadFromFile(audio_location))
		throw "ERROR::AUDIOCOMPONENT::UNABLE_TO_LOAD_AUDIO";

	this->sound.setBuffer(buffer);
}

AudioComponent::~AudioComponent()
{
}

const sf::Sound AudioComponent::getSound()
{
	return sound;
}

void AudioComponent::playSound()
{
	sound.play();
}

void AudioComponent::pauseSound()
{
	sound.pause();
}

void AudioComponent::stopSound()
{
	sound.stop();
}
