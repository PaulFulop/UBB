package model.states.list;

import model.values.Value;

public class OutList extends  MyList<Value> {
    public OutList deepcopy() {
        OutList outListCopy = new OutList();
        for(var value : list)
            outListCopy.add(value.copy());

        return outListCopy;
    }

}
