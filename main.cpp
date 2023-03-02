int main()
{
    srand(0);
    for(int i=0; i<20; i++)
       taskFunc(i, 1 + rand()%4);
    return 0;
}
