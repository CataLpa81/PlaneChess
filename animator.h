#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include<map>

using namespace sf;
//����Ҫ��Animation���Animator���໥���ã���ǰ����Animator�࣬
extern class Animator;
//�����࣬ÿһ��������Ӧһ��Animation
class Animation
{

public:
	//��ʾ�ö����Ƿ��Ѿ����Ź�һ�飬����״̬�л�ʱ�����ݣ�������״̬�л�ʱ��ʼ��
	bool isOver;
	//�ö���������
	sf::String Name;
	//������Ԫ��Animator����Animator��ΪΨһһ���ܷ���Animation˽�г�Ա����
	friend class Animator;
	//�����ĸ���
	void Update();
	//�������캯��
	Animation(sf::String Animation_Name, Vector2i size
		, int start_Frame, int total_Frames, Sprite* sp);
private:

	//��������ͼ
	Texture texture;
	//�������õľ���
	Sprite* sprite;

	//������ͼĿǰ��λ��
	Vector2i Current;
	//������ͼ��ʼ��λ��
	Vector2i Start;
	//������ͼ�ĵ�λ��С
	Vector2i Size;

	//��������ͼ�е���ʼ֡
	int start_Frame;

	//��������֡��
	int total_Frames;
	//����Ŀǰ���ڵ�֡��
	int current_Frame;

	

};
//����������Animtor�������ڽ�ɫ�����ϣ����ڴ�ź͹����ɫ�Ķ���
class Animator
{
public:
	//���캯��
	Animator(){}
	//��Animator��������������Ӷ���
	void AddAnimation(Animation* anim);
	//�л�AnimationĿǰ�Ķ�������Ŀǰ���ŵĶ���������currentAnim��
	void SwitchAnimation(sf::String AnimName);
	//��ȡ�����������е�ĳһ���������������ƣ�
	Animation* getAnimation(sf::String AnimName);
	//������������Ŀǰ���ŵĶ���
	Animation* currentAnim;


private:
	std::map<sf::String, Animation*> AnimList;//�ö����������еĶ����б�

	
	
};