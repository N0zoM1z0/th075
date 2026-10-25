#ifndef TH075_FIGHTER_COMMAND_SELECTION_454BC0_HPP
#define TH075_FIGHTER_COMMAND_SELECTION_454BC0_HPP

// Declaration-only receiver views. Original names, parameter signedness and
// complete owner layouts remain provisional. Never instantiate or embed them.
class SpriteSequenceParametersF154 {
public:
    void SetSamplingMode(unsigned char mode);
    void SetColorMask(unsigned int mask);
};

class FighterCommandSelection454BC0 {
public:
    void SetCommandSelection(int selection, unsigned char mode, unsigned int mask);
};

#endif
