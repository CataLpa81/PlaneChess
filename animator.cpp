#include"animator.h"
#include<iostream>

using namespace sf;

//动画的更新
void Animation::Update()
{
	//
	sf::Rect<int> TRect(Current, Size);
	//设置
	sprite->setTextureRect(TRect);
	//如果当前所在的帧小于总的帧数
	if (current_Frame < total_Frames)
	{
		//动画贴图当前位置加上一个size，相当于往前移动一个贴图
		Current.y += Size.y;
		//当前所在帧加1
		current_Frame++;
	}
	//如果当前所在帧大于总的帧数
	else
	{
		//该动画已经结束过一遍
		isOver = true;
		//当前帧回到起始帧
		current_Frame = start_Frame;
		//当前贴图位置回到起始位置
		Current = Start;
		
	}
}

//Animation的构造函数，用于创建新的Animation时的初始化
Animation::Animation(sf::String Animation_Name, Vector2i size
	, int start_frame, int total_frames, Sprite* sp) :sprite(sp)
{
	//设置动画的名字
	Name = Animation_Name;
	//设置贴图单位的大小
	Size = size;
	//设置动画贴图的起始位置
	Start = Vector2i(0 , 0 + (start_frame - 1) * size.y);
	//设置起始帧
	start_Frame = start_frame;
	//设置总帧数
	total_Frames = total_frames;
	//将当前帧设为起始帧
	current_Frame = start_frame;
	//将当前贴图位置设置为起始位置
	Current = Start;
}


//往Animator中加入一个Animation
void Animator::AddAnimation(Animation* anim)
{
	AnimList.insert(std::pair<sf::String, Animation*>(anim->Name, anim));
}

//切换Animator中当前的动画
void Animator::SwitchAnimation(sf::String AnimName)
{

	currentAnim = AnimList.find(AnimName)->second;
	currentAnim->isOver = false;

}

//获取Animator中的某个Animation
Animation* Animator::getAnimation(sf::String AnimName)
{
	return AnimList.find(AnimName)->second;
}
