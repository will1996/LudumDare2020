//
// Created by W on 10/5/20.
//

#ifndef LUDUMDARE2020_FRAMETICKER_HPP
#define LUDUMDARE2020_FRAMETICKER_HPP
#include"utility"

class FrameTicker {
public:
    FrameTicker(size_t interval):m_interval(interval){};
    bool active(){
        return m_counter == m_interval;
    };
    size_t tick(){
        m_counter++;
        if(m_counter>m_interval)
            m_counter=0;
        return m_counter;
    };
private:
    size_t m_interval;
    size_t m_counter;
};


#endif //LUDUMDARE2020_FRAMETICKER_HPP
