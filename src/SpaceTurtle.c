#include<SpaceTurtle.h>

void InitializeCanvas(int width, int height){
	// Setup width and height
	m_Height = height;
	m_Width = width;
	// printf("Initialized Canvas \n{\n\tWidth=%d\n\tHeight=%d\n}", width, height);
	// Allocate the pixels
	Pixels = malloc(width * height * sizeof(Color));
	// Setup pixels to all be 0
	for(size_t i = 0; i != width * height; ++i){
		Pixels[i] = (Color){0,0,0};
	}
	//Do the same for the changes (For speed)
	PixelChanges = malloc(width * height);
	for(size_t i = 0; i != width * height; ++i){
		PixelChanges[i] = 0;
	}
	//Set Background color to black
	BackGroundColor = (Color){0,0,0};
	//Bool to check if we should exit
	CanvasExit = 0;
	//Stack pointer (For the turtle)
	sp = 640;
	//Canvas Turtle is the turtle that is displayed
	CanvasTurtle = malloc(sizeof(Turtle));
	//m_Angle is the angle used in left and right
	m_Angle = 20;
	// Position is the Position in the source file.
	Position = 0;
	//Setup Canvas Turtle
	*CanvasTurtle = (Turtle){0,0};
	//Allocate Turtle Stack (stack used in the interpreter)
	TurtleStack = malloc(sizeof(Turtle) * 640);
	SDL_CreateWindowAndRenderer(width, height, 0, &m_Window, &m_Renderer);
	SDL_SetWindowTitle(m_Window, "Space-Turtle");
}

void Clear(){
	free(Pixels);
	Pixels = malloc(m_Width * m_Height * sizeof(Color));
}

void BackGround(Color color){
	BackGroundColor = color;
}

void DrawCanvas(){
	SDL_RenderClear(m_Renderer);
	int x = 0;
	int y = 0;
	for(size_t i = 0; i != m_Width * m_Height; ++i){
		if(PixelChanges[i] == 1){
			Color color = Pixels[i];
			SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, 1);
			SDL_RenderDrawPoint(m_Renderer, x,y);
		}
		if(x == m_Width){
			x = 0;
			++y;
		}
		++x;
		SDL_SetRenderDrawColor(m_Renderer, BackGroundColor.r, BackGroundColor.g, BackGroundColor.b, 1);
	}
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:{
					CanvasExit = 1;
			} break;
			case SDL_KEYDOWN:{
				if(event.key.keysym.sym == SDLK_ESCAPE){
					CanvasExit = 1;
				}
			} break;
		}
	}
	SDL_RenderPresent(m_Renderer);
}

void PutPixel(int x, int y, Color color){
	if(x >= m_Width || x <= 0){
		return;
	}
	if(y >= m_Height || y <= 0){
		return;
	}
	Pixels[x + (y * m_Width)] = color;
	PixelChanges[x + (y * m_Width)] = 1;
}

void Push(){
	TurtleStack[sp] = *CanvasTurtle;	
	--sp;
}
void Pop(){
	++sp;
	*CanvasTurtle = TurtleStack[sp];
}

void TurtleForward(){
	Turtle copy = *CanvasTurtle;
	float angle = CanvasTurtle->angle * (PI / 180);
	float speed = sqrt(2 * (CanvasTurtle->speed * CanvasTurtle->speed));
	CanvasTurtle->x += speed * cos(angle);
	CanvasTurtle->y += (-speed) * sin(angle);
	DrawLine((float)CanvasTurtle->x, (float)CanvasTurtle->y, (float)copy.x, (float)copy.y, (Color){255,255,255});
}

void TurtleLeft(){
	CanvasTurtle->angle -= m_Angle;
}
void TurtleRight(){
	CanvasTurtle->angle += m_Angle;
}

void DrawLine(float x0, float y0, float x1, float y1, Color color){
	x0 = (int)x0;
	y0 = (int)y0;
	x1 = (int)x1;
	y1 = (int)y1;
	int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;
    
    while(1){
        PutPixel(x0, y0, color);
        if(x0 == x1 && y0 == y1) return;
        int e2 = 2 * error;
        if(e2 >= dy){
            if(x0 == x1) return;
            error = error + dy;
            x0 = x0 + sx;
        }
        if(e2 <= dx){
            if(y0 == y1) return;
            error = error + dx;
            y0 = y0 + sy;
        }
    }
}
void InterpretCommand(int x){
	char current = Source[Position];

	switch(current){
		case 'F':
		case 'f':{
			TurtleForward();
		} break;
		case '-':{
			TurtleRight();
		} break;
		case '+':{
			TurtleLeft();
		} break;
		case '[':{
			Push();
		} break;
		case ']':{
			Pop();
		} break;
		case '\0':{
			return;
		} break;
		default:{
			++Position;
			InterpretCommand(0);
		}

	}

	++Position;
	if(x == 1000){
		return;
	}else{
		InterpretCommand(x + 1);
	}
}