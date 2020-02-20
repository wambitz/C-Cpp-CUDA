bool isLucky(int n) 
{
    auto accum1 = 0;
    auto accum2 = 0;
    
    int first = n & 0xFFFF000;
    int second = n & 0x0000FFFF;
    
    std::string sfirst = to_string(first);
    std::string ssecond = to_string(second);
    
    for (auto s : sfirst)
    {
        accum1 += s - '0'; 
    }
    
    for (auto s : ssecond)
    {
        accum2 += s - '0'; 
    }
    return accum1 == accum2;
}