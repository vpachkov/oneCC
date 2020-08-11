int func (int a, int b, int c) {
    return a + b + c;
}

int main ()
{
    int a = 1;
    int b = 5;

    a = func(2, 3, 5) + func(2, 3, 5) + func(2, 3, 5);
    return a;
}