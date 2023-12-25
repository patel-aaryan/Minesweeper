#ifndef STATE_H
#define STATE_H

/* State types are:
    Initial -- How I start out.

    Pressed -- I was just pressed.  I am letting you know that.  I would like
               to know if you are a mine.

    Reply -- I am replying to a message you sent me, indicating whether I
             am a mine or not.

    ToPress -- I have a neighbouring cell with no mines next to it, and I
              am going to be pressed

    Propagate -- I have discoverd that I have no mines next to me, and want
                 all of my neighbours to press.

    Done -- My state has bee fully resolved.

    Exploded -- I am a mine and have beeen pressed. The user lost the game
*/
enum class StateType { Initial,
                       Pressed,
                       Reply,
                       ToPress,
                       Propagate,
                       Done,
                       Exploded };

struct State {
  StateType type;  // See above
  // other things as you deem appropriate
};

#endif
