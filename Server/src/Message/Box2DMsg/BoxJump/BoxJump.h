#ifndef __BOXJUMP_H__
#define __BOXJUMP_H__

#include "../Box2DMsg.h"

#include <memory>

class BoxJump : public Box2DMsg {
    bool forward;

    BoxJump(bool is_forward, int id);
public: 
    static std::shared_ptr<Message> jump_fw(int id);
    static std::shared_ptr<Message> jump_bw(int id);

    void get_processed_box2d(BoxManager& box2d) override;

    bool is_forward() const;
};

#endif // !__BOXJUMP_H__
