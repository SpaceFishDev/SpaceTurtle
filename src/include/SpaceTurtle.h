#pragma once
#include<stdlib.h>
#include<stdio.h>
#define SDL_MAIN_HANDLED
#include<SDL/SDL.h>
#include<Math.h>
#define PI 3.14159265359

typedef struct
{
	float x;
	float y;
	float angle;
	float speed;
} Turtle;

Turtle* CanvasTurtle;

Turtle* TurtleStack;

typedef struct 
{
	int r,g,b,a;
} Color;

SDL_Window* m_Window;
SDL_Renderer* m_Renderer;

int m_Width;
int m_Height;
Color* Pixels;
char* PixelChanges;
Color BackGroundColor;
char CanvasExit;
int sp;
float m_Angle;
char* Source;
int Position;

void InitializeCanvas(int width, int height);

void Clear();

void BackGround(Color color);

void DrawCanvas();

void PutPixel(int x, int y, Color color);

void Push();
void Pop();

void DrawLine(float x, float y, float x1, float y1, Color color);

void TurtleForward();
void TurtleLeft();
void TurtleRight();

void InterpretCommand(int x);