#include "Speakerview.cpp"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1; // error checking
    }

    Speakerview *s = new Speakerview();//creates speakerview object to call processfile on
    s->ProcessFile(argv[1]);

    delete s; //deletes the object 

    return 0;
}
