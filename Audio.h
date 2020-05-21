#pragma once
#include<SFML/Audio.hpp>
#include<map>

extern class AudioManager;
extern class Audio;

typedef std::pair<sf::String, Audio*> AudioMapPair;

class Audio
{
protected:
	Audio(sf::String s,bool isLoop)
	{
		buffer.loadFromFile(s);
		sound.setBuffer(buffer);
		if (isLoop)
			sound.setLoop(true);
		else
			sound.setLoop(false);
	}
	friend AudioManager;
	
	sf::SoundBuffer buffer;
	sf::Sound sound;

	void Play();
	void Pause();
	void Stop();
	void ChangeVolume(float delta);
	void SetVolume(float volume);

	
};

class AudioManager
{
public:
	static AudioManager* Instance()
	{
		static AudioManager* instance = new AudioManager();
		return instance;
	}
	

	void Play(sf::String);
	void Stop(sf::String);
	void Pause(sf::String);
	void SetVolume(sf::String,float volume);
	void ChangeVolume(sf::String,float volume);
	void PlayAll();
	void StopAll();
	void PauseAll();
	void SetMute();
	bool isMute=false;


private:
	AudioManager() 
	{
		AudioMap.insert(AudioMapPair("dice", new Audio("./data/Audio/dice.ogg", false)));
		AudioMap.insert(AudioMapPair("msg", new Audio("./data/Audio/message.ogg", false)));
		AudioMap.insert(AudioMapPair("plane", new Audio("./data/Audio/plane.ogg",false)));
		AudioMap.insert(AudioMapPair("BGM", new Audio("./data/Audio/BGM.ogg", false)));
	}

	std::map<sf::String, Audio*> AudioMap;
};

