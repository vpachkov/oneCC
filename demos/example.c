int func (int a, int b, int c) {
    return a + b + c;
}

int main ()
{
    int a = 1;
    int b = 5;
    int c = 5;

    while (a == 1 && b == 5) {
        if (a == 3) {
            c = 3;
        } else {
            c = 2;
        }
    }
    return a;
}