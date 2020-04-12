#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include<map>

using namespace sf;
//由于要让Animation类和Animator类相互调用，提前声明Animator类，
extern class Animator;
//动画类，每一个动画对应一个Animation
class Animation
{

public:
	//表示该动画是否已经播放过一遍，用于状态切换时的依据，并且在状态切换时初始化
	bool isOver;
	//该动画的名字
	sf::String Name;
	//声明友元类Animator，让Animator成为唯一一个能访问Animation私有成员的类
	friend class Animator;
	//动画的更新
	void Update();
	//动画构造函数
	Animation(sf::String Animation_Name, Vector2i size
		, int start_Frame, int total_Frames, Sprite* sp);
private:

	//动画的贴图
	Texture texture;
	//动画作用的精灵
	Sprite* sprite;

	//动画贴图目前的位置
	Vector2i Current;
	//动画贴图起始的位置
	Vector2i Start;
	//动画贴图的单位大小
	Vector2i Size;

	//动画在贴图中的起始帧
	int start_Frame;

	//动画的总帧数
	int total_Frames;
	//动画目前所在的帧数
	int current_Frame;

	

};
//动画控制器Animtor，挂载在角色对象上，用于存放和管理角色的动画
class Animator
{
public:
	//构造函数
	Animator(){}
	//往Animator动画控制器中添加动画
	void AddAnimation(Animation* anim);
	//切换Animation目前的动画，把目前播放的动画保存在currentAnim中
	void SwitchAnimation(sf::String AnimName);
	//获取动画控制器中的某一个动画（根据名称）
	Animation* getAnimation(sf::String AnimName);
	//动画控制器中目前播放的动画
	Animation* currentAnim;


private:
	std::map<sf::String, Animation*> AnimList;//该动画控制器中的动画列表

	
	
};