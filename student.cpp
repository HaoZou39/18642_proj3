/* 
 * Originally by Philip Koopman (koopman@cmu.edu)
 * and Milda Zizyte (milda@cmu.edu)
 *
 * STUDENT NAME:Darius Davis
 * ANDREW ID: dariusd
 * LAST UPDATE: 1/25/18 2:20am
 *
 * This file is an algorithm to solve the ece642rtle maze
 * using the left-hand rule. The code is intentionaly left obfuscated.
 */

//m1.maze file format:
//    first line is start square
//    second line is end square
//    remaining lines are maze walls

// external helper functions.  Don't change these lines!
bool bumped(int xa, int ya, int xb, int yb);
bool atend(int x, int y);
void displayTurtle(int r);

// OK to change below this point


typedef enum {
    up,
    right,
    down,
    left,
    noName
}direction;

typedef enum {
    state0,
    state1,
    state2,
    state5 = 5
}state;

typedef struct coordinates {
    int xa = 0;
    int ya = 0;
    int xb = 0;
    int yb = 0;
}coo;

typedef struct random {
    bool z;
    bool e;
    int m;
    bool b;
    int q;
    int countdown;
    int TIMEOUT = 17; // bigger number slows down simulation so you can see what's happening
}ran;

// this procedure takes one step in the maze and returns   true=done / false=not done

// Ground rule -- you are only allowed to call the three helper functions above, and NO other turtle methods or maze methods (no peeking at the maze!)

bool moveTurtle(QPointF & pos_) {
    static direction d;
    static state s;
    static coo place;
    static ran rando;

    rando.m = true;

    if (rando.countdown == 0) {
        place.xa = pos_.x();
        place.ya = pos_.y();
        place.xb = pos_.x();
        place.yb = pos_.y();

        switch (d) {
        case right:
             place.xb += 1;
             break;
        case up:
             place.yb += 1;
             break;
        case left:
             place.xb += 1;
             place.yb += 1;
             place.ya += 1;
             break;
        case down:
             place.xb += 1;
             place.yb += 1;
             place.xa += 1;
             break;
        default:
             break;
             ROS_ERROR("Movement error");
        }

        rando.b = bumped(place.xa, place.ya, place.xb, place.yb);
        rando.e = atend(pos_.x(), pos_.y());

        /*The if/else statements below make the turtle turn to the right of its relative orientation
          and checks if it bumps into a wall. If it does bump into a wall, it turns the turtle to the
          left of its initial orientation*/

        switch (d) {
        case up:
            switch(s){
              case state2:
                   d = right;
                   s = state1;
                   break;
              case state0:
                   if (rando.b) {
                      d = left;
                      s = state0;
                   }else{ 
                      s = state2;
                   }
                   break;
              case state1:
                   if (rando.b) {
                      d = left;
                      s = state0;
                   }else{ 
                      s = state2;
                   }
                   break;
              case state5:
                   if (rando.b) {
                      d = left;
                      s = state0;
                   }else{ 
                      s = state2;
                   }
                   break;
              default:
                   ROS_ERROR("Up case: state error");
                   break;
            }
            break;

        case left:
            switch(s){
              case state2:
                   d = up;
                   s = state1;
                   break;
              case state0:
                   if (rando.b) {
                      d = down;
                      s = state0;
                   }else{
                      s = state2;
                   }
                   break;
              case state1:
                   if (rando.b) {
                      d = down;
                      s = state0;
                   }else{
                      s = state2;
                   }
                   break;
              case state5:
                   if (rando.b) {
                      d = down;
                      s = state0;
                   }else{
                      s = state2;
                   }
                   break;
              default:
                   ROS_ERROR("Left case: state error");
                   break;
            }
            break;

        case down:
            switch(s){
              case state2:
                   d = left;
                   s = state1;
                   break;
              case state0:
                   if (rando.b) {
                      d = right;
                      s = state0;
                   }else{
                      s = state2;
                   }
                   break;
              case state1:
                   if (rando.b) {
                      d = right;
                      s = state0;
                   }else{
                      s = state2;
                   }
                   break;
              case state5:
                   if (rando.b) {
                      d = right;
                      s = state0;
                   }else{
                      s = state2;
                   }
                   break;
              default:
                   ROS_ERROR("Down case: state error");
                   break;
            }
            break;

        case right:
            switch(s){
              case state2:
                   d = down;
                   s = state1;
                   break;
              case state0:
                   if (rando.b) {
                      d = up;
                      s = state0;
                   }else{
                      s = state2;
                   }
                   break;
              case state1:
                   if (rando.b) {
                      d = up;
                      s = state0;
                   }else{
                      s = state2;
                   }
                   break;
              case state5:
                   if (rando.b) {
                      d = up;
                      s = state0;
                   }else{
                      s = state2;
                   }
                   break;
              default:
                   ROS_ERROR("Right case: state error");
                   break;
            }
            break;

        default:
            ROS_ERROR("Directional error");
            break;
        }

        rando.z = s == 2;
        rando.m = true;

        if (rando.z == true && rando.e == false) {
            switch (d) {
            case noName:
                 pos_.setY(pos_.y() + 0);
                 break;
            case left:
                 pos_.setY(pos_.y() + 1);
                 break;
            case down:
                 pos_.setX(pos_.x() + 1);
                 break;
            case right:
                 pos_.setY(pos_.y() - 1);
                 break;
            case up:
                 pos_.setX(pos_.x() - 1);
                 break;
            default:
                 ROS_ERROR("z & e: directional error");
                 break;
            }
            rando.z = true;
            rando.m = false;
        }
    }

    if (rando.countdown == 0) rando.countdown = rando.TIMEOUT;
    else rando.countdown -= 1;

    // display the turtle -- must call this function before returning!
    displayTurtle(d);
    return (rando.e);
}
