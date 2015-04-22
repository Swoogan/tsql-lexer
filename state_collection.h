#ifndef STATE_COLLECTION_H
#define STATE_COLLECTION_H

#include "state.h"
#include "state_type.h"

class StateCollection {
public:
    StateCollection();
    ~StateCollection();

    void init();
    State* get(StateType type);

private:
    QHash<StateType, State*> states;
};

#endif // STATE_COLLECTION_H
