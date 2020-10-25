int func (int a, int b, int c) {
    return a + b + c;
}

int main ()
{
    int a = 1;
    int b = 5;

    if ((a > 1 || a > 2) && (b > 3 || b > 4)) { 
        b = 6;
    } else {
        b = 1;
    }
    return a;
}