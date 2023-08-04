#include <bits/stdc++.h>

using namespace std;


// created spacecraft class which has all properties and required methods for it.
class Spacecraft
{

private:
    // Assumption=> it will change angle by 90degree for upward/downward.
    // direction will be mapped to the angle
    unordered_map<int, char> ang2dir;

public:
    // indicates position of the spacecraft
    int x, y, z;
    // indicates direction of the spacecraft
    char dir;
    // 2 angles are required => one for horizontal and one for vertical
    int angle1;
    int angle2;

    Spacecraft(int x, int y, int z, char dir)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->dir = dir;

        ang2dir[0] = 'N';
        ang2dir[90] = 'E';
        ang2dir[180] = 'S';
        ang2dir[270] = 'W';

        // as per the direction it will have angle
        bool found = false;    //if direction is up/down
        angle1 = angle2 = 0;
        for (auto pos : ang2dir)
        {
            if (pos.second == dir)
            {
                found = true;
                angle1 = pos.first;
                break;
            }
        }
        if(!found){
            if(dir == 'U')
                angle2 = 90;
            else
                angle2 = 270;
        }
    }

    // for moving in forward or backward direction => in this case direction will be remain same
    void move(char command)
    {

        // based on current direction of the plane we will make changes in coordinates
        if (dir == 'W' || dir == 'E')
        {

            if (command == 'f')
                x += 1;
            else
                x -= 1;
        }
        else if (dir == 'N' || dir == 'S')
        {

            if (command == 'f')
                y += 1;
            else
                y -= 1;
        }
        else
        {

            if (command == 'f')
                z += 1;
            else
                z -= 1;
        }
    }

    // for turning the plane left/right, upward/downward => direction will change
    void turn(char &command)
    {

        unordered_map<char, int> com2ang;
        com2ang['l'] = -90;
        com2ang['r'] = 90;
        // clockwise
        com2ang['u'] = 90;
        com2ang['d'] = -90;

        // for left-right turn angle1 will change and for upward-downward turn angle2 will change.
        if(command == 'l' || command == 'r'){

            angle2 = 0;    //because diagonal moves are not there
            int newAngle = angle1 + com2ang[command];
            angle1 = (newAngle) % 360;

            if (angle1 < 0)
                angle1 += 360;

            dir = ang2dir[angle1];
        }
        else{
            int newAngle = angle2 + com2ang[command];
            angle2 = (newAngle) % 360;

            if (angle2 < 0)
                angle2 += 360;

            if(angle2 == 90){
                dir = 'U';
            }
            else if(angle2 == 270){
                dir = 'D';
            }
            else{
                int temp = (angle1 + angle2) % 360;
                dir = ang2dir[temp];
            }
        }
    }
};

int main()
{

    // current direction of the spacecraft
    char dir;
    cin >> dir;

    // Current position of the spacecraft in coordinates
    int x, y, z;
    cin >> x >> y >> z;

    Spacecraft sc(Spacecraft(x,y,z,dir));

    // sequence of commands wants to operate on spacecraft
    string commands;
    cin >> commands;

    int len = commands.size();
    for (int i = 0; i < len; i++)
    {

        cout << "Command :" << commands[i] << endl;
        if (commands[i] == 'f' || commands[i] == 'b')
            sc.move(commands[i]);
        else
            sc.turn(commands[i]);

        cout << "(X: " << sc.x << ",y: " << sc.y << ",z: " << sc.z << ")   ";
        cout << "direction: ";
        cout << sc.dir << endl
             << endl
             << endl;
    }

    cout << "Final position: ";
    cout << "(X: " << sc.x << ",y: " << sc.y << ",z: " << sc.z << ")\n";
    cout << "Final direction: ";
    cout << sc.dir << endl;

    return 0;
}

/*
Input:
N
0 0 0
frubl

N
0 0 0
ul
uldr
*/