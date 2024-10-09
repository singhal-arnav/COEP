#include "dll.c"

int main() {
    list l;
    init(&l);
    append(&l, 2);
    append(&l, 4);
    append(&l, 5);
    display(l);
    return 0;
}