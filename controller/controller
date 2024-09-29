#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../brick_game/Basemodel.h"

template<typename Model>
class Controller
{
public:
    Controller(Model *game):model(game) {}
    GameInfo_t* Update(UserAction_t action=UserAction_t::Action) {
        return model->UpdateData(action);
    }
private:
    Model *model;
};

#endif // CONTROLLER_H
