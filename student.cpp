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

#define TIMEOUT 17 // bigger number slows down simulation so you can see what's happening

int countdown;

typedef enum {
    up,
    right,
    down,
    left,
    noName
}
direction;

typedef enum {
    state0,
    state1,
    state2,
    state5 = 5
}
state;

typedef struct coordinates {
    int xa = 0;
    int ya = 0;
    int xb = 0;
    int yb = 0;
}
coo;

typedef struct random {
    bool z;
    bool e;
    int m;
    bool b;
    int q;
}
ran;

// this procedure takes one step in the maze and returns   true=done / false=not done

// Ground rule -- you are only allowed to call the three helper functions above, and NO other turtle methods or maze methods (no peeking at the maze!)

bool moveTurtle(QPointF & pos_) {
    static direction d;
    static state s;
    static coo place;
    static ran rando;

    ROS_INFO("Turtle update Called  countdown=%i", countdown);

    rando.m = true;

    if (countdown == 0) {
        ROS_INFO("begin countdown loop" );
        place.xa = pos_.x();
        place.ya = pos_.y();
        place.xb = pos_.x();
        place.yb = pos_.y();

        switch (d) {
        case right:
            place.xb += 1;
            ROS_INFO("countdown loop right case" );
            break;
        case up:
            place.yb += 1;
            ROS_INFO("countdown loop up case" );
            break;
        case left:
            place.xb += 1;
            place.yb += 1;
            place.ya += 1;
            ROS_INFO("countdown loop left case" );
            break;
        case down:
            place.xb += 1;
            place.yb += 1;
            place.xa += 1;
            ROS_INFO("countdown loop down case" );
            break;
        default:
            break;
            //ROS_ERROR
        }

        rando.b = bumped(place.xa, place.ya, place.xb, place.yb);
        rando.e = atend(pos_.x(), pos_.y());

        ROS_INFO("before switch bump = %d" , rando.b );
        ROS_INFO("before switch attend = %d" , rando.e );

        /*The if/else statements below make the turtle turn to the right of its relative orientation
  and checks if it bumps into a wall. If it does bump into a wall, it turns the turtle to the
  left of its initial orientation*/
      ROS_INFO("d value = %i", d );

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
                } else{ 
                    s = state2;
                }
                break;
              case state1:
                if (rando.b) {
                  d = left;
                  s = state0;
                } else{ 
                    s = state2;
                }
                break;
              case state5:
                if (rando.b) {
                  d = left;
                  s = state0;
                } else{ 
                    s = state2;
                }
                break;
              default:
                break; //ROS_ERROR
            }


            ROS_INFO("Switch up State = %i  Switch up Orientation = %i", s, d );
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
                } else {
                  s = state2;
                }
                break;
              case state1:
                if (rando.b) {
                  d = down;
                  s = state0;
                } else {
                  s = state2;
                }
                break;
              case state5:
                if (rando.b) {
                  d = down;
                  s = state0;
                } else {
                  s = state2;
                }
                break;
              default:
                break; //ROS_ERROR
            }

            ROS_INFO("Switch left State = %i  Switch left Orientation = %i", s, d );
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
                } else{
                  s = state2;
                }
                break;
              case state1:
                if (rando.b) {
                  d = right;
                  s = state0;
                } else{
                  s = state2;
                }
                break;
              case state5:
                if (rando.b) {
                  d = right;
                  s = state0;
                } else{
                  s = state2;
                }
                break;
              default:
                break; //ROS_ERROR
            }

            ROS_INFO("Switch down State = %i  Switch down Orientation = %i", s, d );
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
                } else{
                  s = state2;
                }
                break;
              case state1:
                if (rando.b) {
                  d = up;
                  s = state0;
                } else{
                  s = state2;
                }
                break;
              case state5:
                if (rando.b) {
                  d = up;
                  s = state0;
                } else{
                  s = state2;
                }
                break;
              default:
                break; //ROS_ERROR
            }

            ROS_INFO("Switch right State = %i  Switch right Orientation = %i", s, d );
            break;

        default:
              switch (s) {
              case state5:
                  d = left;
                  s = state0;
                  ROS_INFO("Outer switch state5" );
                  break;
              case state0:
                  ROS_INFO("Outer switch state0" );
                  break;
              case state1:
                  ROS_INFO("Outer switch state1" );
                  break;
              case state2:
                  ROS_INFO("Outer switch state2" );
                  break;
              default:
                  ROS_INFO("Outer switch default" );
                  break; //ROS_ERROR
              }
              if (rando.b) {
                  d = right;
                  s = state1;
                  ROS_INFO("Outer switch bump" );
              } else {
                  s = state2;
                  ROS_INFO("Outer switch no bump state2" );
              }
            ROS_INFO("Default State = %i  Default 1 Orientation = %i", s, d );
            break; //ROS_ERROR
        }


        ROS_INFO("Orientation=%i  STATE=%i", d, s);
        rando.z = s == 2;
        rando.m = true;

        ROS_INFO("rando.z = %d" , rando.z );
        ROS_INFO("rando.m = %d" , rando.m );
        ROS_INFO("rando.e = %d" , rando.e );

        if (rando.z == true && rando.e == false) {
          ROS_INFO("rando.z is true and rando.e is false" );
            switch (d) {
            case noName:
                pos_.setY(pos_.y() + 0);
                ROS_INFO("z & e noName case" );
                break;
            case left:
                pos_.setY(pos_.y() + 1);
                ROS_INFO("z & e left case" );
                break;
            case down:
                pos_.setX(pos_.x() + 1);
                ROS_INFO("z & e down case" );
                break;
            case right:
                pos_.setY(pos_.y() - 1);
                ROS_INFO("z & e right case" );
                break;
            case up:
                pos_.setX(pos_.x() - 1);
                ROS_INFO("z & e up case" );
                break;
            default:
                ROS_INFO("z & e default case" );
                break; //ROS_ERROR
            }
            rando.z = true;
            rando.m = false;
        }
    
    }
    if (countdown == 0) countdown = TIMEOUT;
    else countdown -= 1;

    // display the turtle -- must call this function before returning!
    displayTurtle(d);
    return (rando.e);
}
