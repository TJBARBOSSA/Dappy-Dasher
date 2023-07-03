#include<cstdio>
#include<iostream>
#include"raylib.h"
using namespace std;

struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;

};
bool isOnGround(AnimData data, int windowheight){
return data.pos.y>= windowheight- data.rec.height;
};

AnimData updateAnimData(AnimData data, float deltatime, int maxFrame){

    //update running time
    data.runningTime += deltatime;
    if (data.runningTime >=data.updateTime){
        data.runningTime = 0.0;
        //update animation time
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if(data.frame > maxFrame){
            data.frame = 0;
        }
    }
    return data;
};
int main(){

//Window Properties
int windowDimension[2];
windowDimension[0] = 512;
windowDimension[1] = 380;    
// const int WindowWidth{512};
// const int WindowHeight{380};
InitWindow(windowDimension[0],windowDimension[1],"Dappy Dasher by TjBarbossa (Credits to course of www.gamedev.tv)");

//rectangle dimensions
// const int width{50};
// const int height{80};

//check if rectangle is in air
bool isInAir ;
//gravity (pixels/s)/s;
const int gravity{1300};

//nebula variables
Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
// Rectangle nebRec{0.0,0.0,nebula.width/8,nebula.height/8};
// Vector2 nebPos{WindowWidth,WindowHeight - nebRec.height};

// Rectangle neb2rec{0.0,0.0,nebula.width/8,nebula.height/8};
// Vector2 neb2Pos{WindowWidth + 600 ,WindowHeight - nebRec.height };

//AnimData for nebula
// AnimData nebData{
//     {0.0,0.0,nebula.width/8,nebula.height/8},//rectangle rec
//     {windowDimension[0] ,windowDimension[1] - nebula.height/8},//vector2 pos
//     0, // int frame
//     1.0/12.0, //float update time
//     0}; // float running time

// //AnimData for neb2
// AnimData neb2Data{{0.0,0.0,nebula.width/8,nebula.height/8},{windowDimension[0]  + 600 ,windowDimension[1] - nebula.height/8},0,1.0/20.0,0.0};

//Array of nebulei
const int sizeOfNebulai{10};
AnimData nebulei[sizeOfNebulai]{};
for (int i =0;i<sizeOfNebulai;i++){
    nebulei[i].rec.x = 0.0;
    nebulei[i].rec.y = 0.0;
    nebulei[i].rec.width = nebula.width/8;
    nebulei[i].rec.height = nebula.height/8;

    nebulei[i].pos.y = windowDimension[1]- nebula.height/8;

    nebulei[i].frame = 0;
    nebulei[i].runningTime = 0.0;
    nebulei[i].updateTime = 1.0/20.0;
    nebulei[i].pos.x = windowDimension[0]+i*400; 
}


//finish line
float finishLine{nebulei[sizeOfNebulai - 1].pos.x };

// nebulei[0].pos.x = windowDimension[0];
// nebulei[1].pos.x = windowDimension[0]+600;
// nebulei[2].pos.x = windowDimension[0]+1200;
//nebula x velocity
int nebVel{-200};

//scarfy variables
Texture2D scarfy = LoadTexture("textures/scarfy.png");
AnimData scarfyData;
scarfyData.rec.width=scarfy.width/6;
scarfyData.rec.height =scarfy.height;
scarfyData.rec.x= 0;
scarfyData.rec.y=0;
scarfyData.pos.x = windowDimension[0]/2 - scarfy.width/6;
scarfyData.pos.y = windowDimension[1] - scarfy.height;
// Rectangle scarfyRec;
// scarfyRec.width =scarfy.width/6;
// scarfyRec.height=scarfy.height;
// scarfyRec.x = 0;
// scarfyRec.y =0;
// Vector2 scarfyPos;
// scarfyPos.x = WindowWidth/2 - scarfyRec.width/2;
// scarfyPos.y = WindowHeight - scarfyRec.height;

//animation frame scarfy
//int frame{};
scarfyData.frame =0;

 
//animation frame nebula
//int nebFrame{};
//int neb2Frame{};
//const float neb2pdateTime{1.0/20.0};
//float neb2RunningTime{};

//update time for scarfy
// const float updateTime = 1.0/12.0;
scarfyData.updateTime = 1.0/12.0;
//update time for nebula
//const float nebUpdateTime{1.0/12.0};

//running time (time passed since last time updated the animation frame)
//float runningTime{}; //scarfy
scarfyData.runningTime = 0;
//float nebRunningTime{};//nebula

//int posY{WindowHeight - height};
const int jumpval{-725};
int velocity{40};

//jumpvelocity pixels per second


//background texture
Texture2D Background = LoadTexture("textures/far-buildings.png");
float bgX{};

//midground texture
Texture2D MidGround = LoadTexture("textures/back-buildings.png");
float mgX{};

//Foreground texture
Texture2D Foreground = LoadTexture("textures/foreground.png");
float fgX{};
bool collision{};

SetTargetFPS(60);
while(!WindowShouldClose()){
    
//Delta time (time since last frame)
const float dT = GetFrameTime();


BeginDrawing();

ClearBackground(WHITE);

bgX -= 20* dT;

if (bgX<= -Background.width*2){
    bgX = 0.0;
}

mgX -= 40*dT;
if (mgX <= -MidGround.width*2){
    mgX = 0.0;
}

fgX -= 80*dT;
if (fgX <= -Foreground.width*2){
    fgX = 0.0;
}

//drawing background
Vector2 bg1Pos{bgX,0.0};
DrawTextureEx(Background,bg1Pos,0.0,2.0,WHITE);
Vector2 bg2Pos{bgX + Background.width*2, 0.0};
DrawTextureEx(Background, bg2Pos ,0.0 , 2.0, WHITE);

//drawing midground
Vector2 mg1pos{mgX,0.0};
Vector2 mg2pos{mgX+MidGround.width*2,0.0};
DrawTextureEx(MidGround,mg1pos,0.0,2.0,WHITE);
DrawTextureEx(MidGround,mg2pos,0.0,2.0,WHITE);

//drawing foreground
Vector2 fg1pos{fgX,0.0};
Vector2 fg2pos{fgX+Foreground.width*2,0.0};
DrawTextureEx(Foreground,fg1pos,0.0,2.0,WHITE);
DrawTextureEx(Foreground,fg2pos,0.0,2.0,WHITE);

//ground check
if(isOnGround(scarfyData, windowDimension[1])){
//rectangle is on ground
velocity = 0;
isInAir = false;
}else{
    
    //rectangle is in air
    velocity += gravity*dT;
    isInAir = true;}

//jump check
if (IsKeyPressed(KEY_SPACE) && !isInAir){
    velocity +=jumpval;
}

// //update nebula position
// nebulei[0].pos.x += nebVel *dT;
// //update nebula 2 position
// nebulei[1].pos.x +=nebVel*dT;
//update nebulei pos
for (int i = 0; i<sizeOfNebulai;i++){
    nebulei[i].pos.x +=nebVel*dT;
}
finishLine+= nebVel*dT; // update finish line
//Update scarfy position everyframe
scarfyData.pos.y += velocity*dT;

//update scarfys animation frame
//update running time
// scarfyData.runningTime +=dT;
// if(scarfyData.runningTime>=scarfyData.updateTime){
//     scarfyData.runningTime =0;
//     //update animation frame
// scarfyData.rec.x = scarfyData.frame*scarfyData.rec.width;
// scarfyData.frame++;
// if (scarfyData.frame>5){scarfyData.frame = 0;}
// } }
if(!isInAir){
scarfyData = updateAnimData(scarfyData, dT, 5);}
// update nebula animation frame
for (int i = 0; i < sizeOfNebulai; i++){
        // nebulei[i].runningTime += dT;
        // if (nebulei[i].runningTime >= nebulei[i].updateTime)
        //     nebulei[i].runningTime = 0.0;
        //     nebulei[i].rec.x = nebulei[i].frame * nebulei[i].rec.width;
        //     nebulei[i].frame++;
        //     if (nebulei[i].frame > 7)
        //     { 
        //         nebulei[i].frame = 0;
        //     }
        nebulei[i] = updateAnimData(nebulei[i],dT,7);
        }

// //Update nebula 2 animation frame
// nebulei[1].runningTime +=dT;
// if (nebulei[1].runningTime>=nebulei[1].updateTime){
//     nebulei[1].runningTime =0.0;
//     nebulei[1].rec.x = nebulei[1].frame*nebulei[1].rec.width;
//     nebulei[1].frame++;
//     if (nebulei[1].frame>7){
//         nebulei[1].frame =0;
//     }
//}

// //Draw nebula
// DrawTextureRec(nebula,nebulei[i].rec,nebulei[i].pos,WHITE);
// //Draw Second Nebula 
// DrawTextureRec(nebula,nebulei[i].rec,nebulei[i].pos,RED);

//DrawRectangle(WindowWidth/2, posY,width,height,BLUE);


//collision detection

for(AnimData nebula: nebulei){

        float pad{50};
        Rectangle nebRec{nebula.pos.x +pad , nebula.pos.y+pad ,nebula.rec.width -pad*2, nebula.rec.height-pad*2 };
        Rectangle scarfyRec{scarfyData.pos.x,scarfyData.pos.y,scarfyData.rec.width,scarfyData.rec.height};
        if (CheckCollisionRecs(nebRec,scarfyRec)){
            collision = true;
        }
}

if (collision){

     //lose the game
     DrawText("Game Over!", windowDimension[0]/4, windowDimension[1]/2, 40, RED);
   

}else if (scarfyData.pos.x >= finishLine)
{
    DrawText("You Win!", windowDimension[0]/4, windowDimension[1]/2, 40, RED);
}
else{
     //draw nebulai
for ( int i = 0; i < sizeOfNebulai; i++)
{
    DrawTextureRec(nebula, nebulei[i].rec, nebulei[i].pos, WHITE);
}

// // draw nebula
// DrawTextureRec(nebula, nebulei[0].rec, nebulei[0].pos, WHITE);
// // draw nebula
// DrawTextureRec(nebula, nebulei[1].rec, nebulei[1].pos, WHITE);
// // draw nebula
// DrawTextureRec(nebula, nebulei[2].rec, nebulei[2].pos, WHITE);



//Draw scarfy
DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

}
//stop drawing
EndDrawing();
}
UnloadTexture(scarfy);
UnloadTexture(nebula);
UnloadTexture(Background);
UnloadTexture(MidGround);
UnloadTexture(Foreground);
CloseWindow();
return 0;}