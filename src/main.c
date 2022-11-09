#include <conio.h>
#include<SpaceTurtle.h>
//Read entire file into a character array
char *loadfile(char *file)
{
    FILE *fp;
    long lSize;
    char *buffer;
    //Open file and check for error
    fp = fopen ( file , "rb" );
    if( !fp ) perror(file),exit(1);
    //Get Length of file
    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );
	//Allocate buffer
    buffer = calloc( 1, lSize+1 );
    if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);
    //Read file
    if( 1!=fread( buffer , lSize, 1 , fp) )
      fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);
  	//Close and Return
    fclose(fp);
    return buffer;
}

int main(int argc, char** argv){
	//Check if source file is provided
	if(argc == 1){
		printf("Please provide a source file.");
		return - 1;
	}
	else{
		//Set global source to the source file
		Source = loadfile(argv[1]);
	}
	InitializeCanvas(1200 ,1000);
	//Setup the turtle
	CanvasTurtle->x = 500;
	CanvasTurtle->y = 500; //[f[+f[+f][-f]][-f[+f][-f]]]

	CanvasTurtle->speed = 20.0f;
	CanvasTurtle->angle = 90;
	m_Angle = 15.0f;
	//Main loop
	while(!CanvasExit){
		//Interpret current character
		InterpretCommand(0);
		//Draw the canvas
		DrawCanvas();
	}
}