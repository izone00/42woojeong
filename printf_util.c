void    put_space(int len, int is_zero)
{
    char    space;

    if (is_zero)
        space = '0';
    else
        space = ' ';
    while (len-- > 0)
        write(1, &space, 1);
}

int len_int(int num)
{
    int len;

    len = 1;
    while (num / 10)
    {
        len++;
        num /= 10;
    }
    return (len);
}

void    put_int(int num, int *opt, int num_len, int word_len)
{
    int digit;

    if (num < 0)
        write(1, "-", 1);
    else if (opt[space] == 1)
        write(1, " ", 1);
    else if (opt[plus] == 1)
        write(1, "+", 1);
    else
        word_len++;
    put_space(word_len - num_len - 1, 1);
    ft_putnbr(num);        
}

void    print_int(int num, int *opt)
{
    int word_len;
    int num_len;
    
    num_len = len_int(num);
    word_len = num_len;
    if (num_len < opt[presicion])
        word_len = opt[presicion];
    if (num < 0 || opt[plus] == 1 || opt[space] == 1)
        word_len++;
    if (!opt[minus])
    {
        put_space(width - word_len, opt[zero] * (!opt[presicion]));
        put_int(num, opt, num_len, word_len);
    }
    else
    {
        put_int();
        put_space(width - word_len, 0);
    }
}

void    print_char(char ch, int *opt)
{
    int word_len;

    word_len = 1;
    if (!opt[minus])
    {
        put_space(width - word_len, 0);
        write(1, &ch, 1);
    }
    else
    {
        write(1, &ch, 1);
        put_space(width - word_len, 0);
    }
}

void    print_unsigned_int(unsigned int num, int *opt)
{
    int word_len;
    

    word_len = len_ul((unsigned long)num, opt);
    if (!opt[minus])
    {
        put_space(width - word_len, opt[zero]);
        put_uint();
    }
    else
    {
        put_uint();
        put_space(width - word_len, 0);
    }
}

void    print_sixteen(unsigned int hexa, int *opt)
{
    int word_len;
    

    word_len = len_ul((unsigned long)hexa, opt);
    if (!opt[minus])
    {
        put_space(width - word_len, opt[zero]);
        put_hexa(hexa, opt[shop]);
    }
    else
    {
        put_hexa(hexa, opt[shop]);
        put_space(width - word_len, 0);
    }
}

void    print_adress(unsigned long addr, int *opt)
{
    int word_len;
    

    word_len = len_ul(addr, opt);
    if (!opt[minus])
    {
        put_space(width - word_len, opt[zero]);
        put_hexa(hexa, 1);
    }
    else
    {
        put_hexa(hexa, 1);
        put_space(width - word_len, 0);
    }
}

void    print_string(char *str, int *opt)
{
    //presicion 무시 width는 적용
    int word_len;
    

    word_len = ft_strlen(str);
    if (!opt[minus])
    {
        put_space(opt[width] - word_len, 0);
        write(1, str, word_len);
    }
    else
    {
        write(1, str, word_len);
        put_space(opt[width] - word_len, 0);
    }
}