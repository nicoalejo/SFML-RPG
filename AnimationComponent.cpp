#include "AnimationComponent.h"

//Constructors / destructors

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet):
	sprite(sprite), textureSheet(texture_sheet), lastAnimation(nullptr), priorityAnimation(nullptr)
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

//Functions

void AnimationComponent::addAnimation(const std::string key, float animation_timer, 
	int start_frame_x, int start_frame_y, int frames_x,
	int frames_y, int width, int height)
{
	this->animations[key] = new Animation(this->sprite, this->textureSheet,
		animation_timer, start_frame_x, start_frame_y,
		frames_x, frames_y, width, height);
}

void AnimationComponent::checkLastAnimation(const std::string key)
{
	if (this->lastAnimation != this->animations[key]) {
		if (this->lastAnimation != nullptr) {
			this->lastAnimation->reset();
		}
		this->lastAnimation = this->animations[key];
	}
}

void AnimationComponent::play(const std::string key, const float& dt, const bool priority)
{
	//If a priority animation needs to be played
	if (this->priorityAnimation) {
		if (this->priorityAnimation == this->animations[key]) {
			checkLastAnimation(key);
			//If the priority animation is done remove it
			if (this->animations[key]->play(dt))
				this->priorityAnimation = nullptr;
		}
	}
	else {
		if (priority)
			this->priorityAnimation = this->animations[key];

		checkLastAnimation(key);
		this->animations[key]->play(dt);
	}
	
}

void AnimationComponent::play(const std::string key, const float& dt, const float& modifier, 
	const float& modifier_max, const bool priority)
{
	if (this->priorityAnimation) {
		if (this->priorityAnimation == this->animations[key]) {
			checkLastAnimation(key);
			if(this->animations[key]->play(dt, abs(modifier / modifier_max)))
				this->priorityAnimation = nullptr;
		}
	}
	else {
		if (priority) 
			this->priorityAnimation = this->animations[key];
		
		checkLastAnimation(key);
		this->animations[key]->play(dt, abs(modifier / modifier_max));
	}
	
}


