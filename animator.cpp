#include"animator.h"
#include<iostream>

using namespace sf;

//�����ĸ���
void Animation::Update()
{
	//
	sf::Rect<int> TRect(Current, Size);
	//����
	sprite->setTextureRect(TRect);
	//�����ǰ���ڵ�֡С���ܵ�֡��
	if (current_Frame < total_Frames)
	{
		//������ͼ��ǰλ�ü���һ��size���൱����ǰ�ƶ�һ����ͼ
		Current.y += Size.y;
		//��ǰ����֡��1
		current_Frame++;
	}
	//�����ǰ����֡�����ܵ�֡��
	else
	{
		//�ö����Ѿ�������һ��
		isOver = true;
		//��ǰ֡�ص���ʼ֡
		current_Frame = start_Frame;
		//��ǰ��ͼλ�ûص���ʼλ��
		Current = Start;
		
	}
}

//Animation�Ĺ��캯�������ڴ����µ�Animationʱ�ĳ�ʼ��
Animation::Animation(sf::String Animation_Name, Vector2i size
	, int start_frame, int total_frames, Sprite* sp) :sprite(sp)
{
	//���ö���������
	Name = Animation_Name;
	//������ͼ��λ�Ĵ�С
	Size = size;
	//���ö�����ͼ����ʼλ��
	Start = Vector2i(0 , 0 + (start_frame - 1) * size.y);
	//������ʼ֡
	start_Frame = start_frame;
	//������֡��
	total_Frames = total_frames;
	//����ǰ֡��Ϊ��ʼ֡
	current_Frame = start_frame;
	//����ǰ��ͼλ������Ϊ��ʼλ��
	Current = Start;
}


//��Animator�м���һ��Animation
void Animator::AddAnimation(Animation* anim)
{
	AnimList.insert(std::pair<sf::String, Animation*>(anim->Name, anim));
}

//�л�Animator�е�ǰ�Ķ���
void Animator::SwitchAnimation(sf::String AnimName)
{

	currentAnim = AnimList.find(AnimName)->second;
	currentAnim->isOver = false;

}

//��ȡAnimator�е�ĳ��Animation
Animation* Animator::getAnimation(sf::String AnimName)
{
	return AnimList.find(AnimName)->second;
}
