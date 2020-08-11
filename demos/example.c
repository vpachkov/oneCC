int func (int a, int b, int c) {
    return a + b + c;
}

int main ()
{
    int a = 1;
    int b = 5;
    int c = 5;

    a = func(1, 2, 4);
    b = func(1, 2, 4);
    c = func(1, 2, 4);

    while (a == 1) {
        a = 2;
    }
    return a;
}