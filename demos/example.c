int func (int a, int b, int c) {
    return a + b - c;
}

int main ()
{
    int a = 1;
    int b = 5;


    if (b == 5 || a == 1) {
        b = a;
    } else {
        a = b;
    }
    a = func(1, a, 3);
    b = a;
    a = 1 + 2;
    // return a;
}