int func (int a, int b, int c) {
    return a + b - c;
}

int main ()
{
    int a = 1;
    int b = 5;


    if ((a == 1 && b == 2) && (a == 2 && b == 1)) {
        b = a;
    }
    a = func(1, a, 3);
    b = a;
    a = 1 + 2;
    // return a;
}