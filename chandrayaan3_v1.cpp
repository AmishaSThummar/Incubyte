#include<bits/stdc++.h>

using namespace std;

// for moving in forward or backward direction => in this case direction will be remain same
void move(int &x, int &y, int &z,char &currDir, char command){

    // based on current direction of the plane we will make changes in coordinates
    if(currDir == 'W' || currDir == 'E'){

        if(command == 'f')
            x += 1;
        else
            x -= 1;
    }
    else if(currDir == 'N' || currDir == 'S'){

        if(command == 'f')
            y += 1;
        else
            y -= 1;
    }
    else{

        if(command == 'f')
            z += 1;
        else
            z -= 1;
    }
}

// for turning the plane left/right, upward/downward => direction will change
void turn(char &dir, char &command, int &angle, unordered_map<int,char> &ang2dir){

    unordered_map<char,int> com2ang;
    com2ang['l'] = -90;
    com2ang['r'] = 90;

    if(angle < 180){
        com2ang['u'] = -90;
        com2ang['d'] = 90;
    }
    else{
        com2ang['u'] = 90;
        com2ang['d'] = -90;
    }

    int newAngle = angle + com2ang[command];
    angle = (newAngle)%360;

    while(angle<0)
        angle += 360;

    // if command is nither upward or backward then direction as per angle.
    if(command != 'u' && command != 'd'){
        char newDir = ang2dir[angle];
        dir = newDir;
    }
    else dir = command - 'a'+'A';
}

int main(){

    // current direction of the spacecraft
    char dir;
    cin>>dir;

    // Current position of the spacecraft in coordinates
    int x, y, z;
    cin>>x>>y>>z;

    // sequence of commands wants to operate on spacecraft
    string commands;
    cin>>commands;
    

    // Assumption=> it will change angle by 45degree for upward/downward.
    // direction will be mapped to the angle
    unordered_map<int,char> ang2dir;
    ang2dir[0] = 'N';
    ang2dir[90] = 'E';
    ang2dir[180] = 'S';
    ang2dir[270] = 'W';

    // as per the direction it will have angle
    int angle;
    for(auto pos:ang2dir){
        if(pos.second == dir){
            angle = pos.first;
            break;
        }
    }

    int len = commands.size();
    for(int i=0 ; i<len ; i++){

        cout<<"Command :"<<commands[i]<<endl; 
        if(commands[i] == 'f' || commands[i] == 'b')
            move(x, y, z, dir, commands[i]);
        else
            turn(dir, commands[i], angle, ang2dir);
            
        cout<<"(X: "<<x<<",y: "<<y<<",z: "<<z<<")   ";
        cout<<"direction: ";
        cout<<dir<<endl<<endl<<endl;

    }

    cout<<"Final position: ";
    cout<<"(X: "<<x<<",y: "<<y<<",z: "<<z<<")\n";
    cout<<"Final direction: ";
    cout<<dir<<endl;

    return 0;
}

/*
Input:
N
0 0 0 
frubl
*/