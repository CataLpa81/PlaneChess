#include"Audio.h"
#include<iostream>
void Audio::Play()
{
	sound.play();
}

void Audio::Pause()
{
	sound.pause();
}

void Audio::Stop()
{
	sound.stop();
}


void Audio::ChangeVolume(float delta)
{
	sound.setVolume(sound.getVolume() + delta);
}
void Audio::SetVolume(float volume)
{
	sound.setVolume(volume);
}

void AudioManager::Play(sf::String s)
{
	AudioMap.find(s)->second->Play();
}

void AudioManager::Stop(sf::String s)
{
	AudioMap.find(s)->second->Stop();
}

void AudioManager::Pause(sf::String s)
{
	AudioMap.find(s)->second->Pause();
}


void AudioManager::SetVolume(sf::String s,float volume)
{
	AudioMap.find(s)->second->SetVolume(volume);
}

void AudioManager::ChangeVolume(sf::String s, float volume)
{
	AudioMap.find(s)->second->ChangeVolume(volume);
}

void AudioManager::PlayAll()
{
	for (auto a : AudioMap)
	{
		a.second->Play();
	}
}

void AudioManager::StopAll()
{
	for (auto a : AudioMap)
	{
		a.second->Stop();
	}
}

void AudioManager::PauseAll()
{
	for (auto a : AudioMap)
	{
		a.second->Pause();
	}
}

void AudioManager::SetMute()
{
	if(!isMute)
	for (auto iter = AudioMap.begin();
		iter != AudioMap.end();iter++)
	{
		iter->second->SetVolume(0);
		isMute = true;
	}
	else
	for (auto iter = AudioMap.begin();
		iter != AudioMap.end();iter++)
	{
		iter->second->SetVolume(80);
		isMute = false;
	}
}