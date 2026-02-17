#ifndef MINIGIN_TIME_HPP
#define MINIGIN_TIME_HPP

namespace Time
{
    float get_delta_time();
    float get_frame_rate();

    // TODO put in separate (non-public) header file
    void pre_update();
    void post_update();
}

#endif //MINIGIN_TIME_HPP