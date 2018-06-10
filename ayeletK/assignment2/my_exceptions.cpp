#include <exception>

// --------------------- Exceptions --------------------- //
class elementExiststException : public exception{
    virtual const char* what() const throw(){
        return "Element with the given key already exists in the tree";
    }
};
class emptyTreeException : public exception{
    virtual const char* what() const throw(){
        return "The given tree is empty.";
    }
};
class keyNotExistsException : public exception{
    virtual const char* what() const throw(){
        return "The given key does not exists in the given tree.";
    }
};
class illegalPathException : public exception{
    virtual const char* what() const throw(){
        return "Illegal path";
    }
};
class nullNodeException : public exception{
    virtual const char* what() const throw(){
        return "Null node was given as parameter.";
    }
};
class nodeNotExistsException : public exception{
    string node_name;
public:
    nodeNotExistsException(string node_name): node_name(node_name) {}
    virtual const char* what() const throw(){
        string msg = node_name + " does not exists in the given tree.";
        const char *Msg = msg.c_str();
        return Msg;
    }
};
