#ifndef PROJETOEXEC_BOX_H
#define PROJETOEXEC_BOX_H

class Box {
public:
    const int boxCod = 2;
    float length = 0;
    float dimension = 0;
    static Box* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    void Read_File(std::ifstream file);
    std::string toString() const;

};

#endif