#include <unistd.h>
//#include <stdio.h>//////////////////////////////

int     ft_strlen(const char *str)//////////////////////////// 지워
{
        int     i;

        i = 0;
        while (str[i] != '\0')
                i++;
        return (i);
}

typedef struct s_container {
    int     sign[2];
    char    str[30];                
    int     zero_len;
    int     space_len;
} t_container;

enum    option {
    flag = 0,
    width = 5,
    precision = 6,
    type = 7
};
enum    flag {
    minus = 0,
    plus = 1,
    zero = 2,
    space = 3,
    shop = 4
};

void    init_container(t_container *con)
{
    int idx;

    idx = 0;
    (con -> sign)[0] = 0;
    (con -> sign)[1] = 0;
    con -> zero_len = 0;
    con -> space_len = 0;
    while (idx < 30)
    {
        (con -> str)[idx] = 0;
        idx++;
    }
}

int get_str(t_container *conInt, int num)
{
    int f_sign;
    int idx;

    f_sign = 1;
    if (num < 0)
        f_sign = -1;
    idx = 0;
    if (num == 0)
        (conInt -> str)[idx++] = '0';
    while (num)
    {
        (conInt -> str)[idx] = (num % 10) * f_sign + '0';//거꾸로 넣는다. 출력할때 거꾸로 해야됨
        num /= 10;
        idx++;
    }
    (conInt -> str)[idx] = '\0';
    return (idx);
}

int get_int_sign(int *opt, int num)
{
    if (num < 0)
        return ('-');
    else if (opt[plus])
        return ('+');
    else if (opt[space])
        return (' ');
    else
        return (0); 
}
int get_zero(int num_len, int *opt, int *sign)
{
    if (opt[precision] > 0) //정확도에 대한 정보가 있을때
    {
        if (opt[precision] > num_len) //정확도가 숫자의 길이를 넘을때
            return (opt[precision] - num_len);
        else
            return (0);
    }
    else if (opt[zero]) //정확도에 대한 정보가 없고 '0'flag가 쓰일때 ('-'플래그의 유무를 고려해야됨!!!!!!!!!!!)
    {
        num_len += (sign[0] != 0);//부호의 첫칸
        num_len += (sign[1] != 0);//부호의 두번째칸 16진수에서 사용됨
        return (opt[width] - num_len);
    }
    else //정확도에 대한 정보가없고 '0'flag가쓰이지않을때
        return (0); 
}

int get_space(t_container conInt, int *opt, int num_len)
{
    int word_len;

    word_len = 0;
    word_len += num_len;
    word_len += (conInt.sign[0] != 0);
    word_len += (conInt.sign[1] != 0);
    word_len += conInt.zero_len;
    if (word_len < opt[width])
        return (opt[width] - word_len);
    else
        return (0);
}

void    right_align(t_container conInt, int len)
{
    int idx;
    while ((conInt.space_len)--)
        write(1, " ", 1);
    if (conInt.sign[0] != 0)
        write(1, &(conInt.sign[0]), 1);
    if (conInt.sign[1] != 0)
        write(1, &(conInt.sign[1]), 1);
    while ((conInt.zero_len)--)
        write(1, "0", 1);
    idx = len - 1; //인덱스를 끝에서 부터 시작해 반대로 출력한다.
    while (idx >= 0)
    {
        write(1, conInt.str + idx, 1); 
        idx --;
    }
}
void    left_align(t_container conInt, int len)
{
    int idx;

    if (conInt.sign[0] != 0)
        write(1, &(conInt.sign[0]), 1);
    if (conInt.sign[1] != 0)
        write(1, &(conInt.sign[1]), 1);
    while ((conInt.zero_len)--)
        write(1, "0", 1);
    idx = len - 1; //인덱스를 끝에서 부터 시작해 반대로 출력한다.
    while (idx >= 0)
    {
        write(1, conInt.str + idx, 1); 
        idx --;
    }
    while ((conInt.space_len)--)
        write(1, " ", 1);
}
void    print_int(int num, int *opt)
{
    t_container conInt;
    int num_len;

    init_container(&conInt);
    num_len = get_str(&conInt, num);
    conInt.sign[0] = get_int_sign(opt, num);
    conInt.zero_len = get_zero(num_len, opt, conInt.sign);
    conInt.space_len = get_space(conInt, opt, num_len);
    if (opt[minus])
        left_align(conInt, num_len);
    else
        right_align(conInt, num_len);
}

int get_unsign_str(t_container *conUl, unsigned long num)
{
    int idx;
;
    idx = 0;
    if (num == 0)
        (conUl -> str)[idx++] = '0';
    while (num)
    {
        (conUl -> str)[idx] = (num % 10) + '0';//거꾸로 넣는다. 출력할때 거꾸로 해야됨
        num /= 10;
        idx++;
    }
    (conUl -> str)[idx] = '\0';
    return (idx);
}

void    print_unsigned_int(unsigned long num, int *opt)
{
    t_container conUl;
    int num_len;

    init_container(&conUl);
    num_len = get_unsign_str(&conUl, num);
    conUl.zero_len = get_zero(num_len, opt, conUl.sign);
    conUl.space_len = get_space(conUl, opt, num_len);
    if (opt[minus])
        left_align(conUl, num_len);
    else
        right_align(conUl, num_len);
}

int get_hexa_str(t_container *conUl, unsigned long hexa, int type)
{
    int idx;
;
    idx = 0;
    if (hexa == 0)
        (conUl -> str)[idx++] = '0';
    while (hexa)
    {
        if (hexa % 16 <= 9)
            (conUl -> str)[idx] = (hexa % 16) + '0';//거꾸로 넣는다. 출력할때 거꾸로 해야됨
        else if (type == 'X')
            (conUl -> str)[idx] = (hexa % 16) + 55;//소문자로 표시
        else
            (conUl -> str)[idx] = (hexa % 16) + 87;//대문자로 표시
        hexa /= 16;
        idx++;
    }
    (conUl -> str)[idx] = '\0';
    return (idx);
}

void    get_hexa_sign(t_container *conUl, int shop)
{
    if (shop == 1)
    {
        (conUl -> sign)[0] = '0';
        (conUl -> sign)[1] = 'x';
    }
}

void    print_sixteen(unsigned int hexa, int *opt)
{
    t_container conUl;
    int num_len;

    init_container(&conUl);
    num_len = get_hexa_str(&conUl, hexa, opt[type]);
    get_hexa_sign(&conUl, opt[shop]);
    conUl.zero_len = get_zero(num_len, opt, conUl.sign);
    conUl.space_len = get_space(conUl, opt, num_len);
    if (opt[minus])
        left_align(conUl, num_len);
    else
        right_align(conUl, num_len);
}


void    print_adress(unsigned long addr, int *opt)
{
    t_container conUl;
    int num_len;

    init_container(&conUl);
    num_len = get_hexa_str(&conUl, addr, opt[type]);
    get_hexa_sign(&conUl, 1);//opt[shop] = 1 대입
    conUl.zero_len = get_zero(num_len, opt, conUl.sign);
    conUl.space_len = get_space(conUl, opt, num_len);
    if (opt[minus])
        left_align(conUl, num_len);
    else
        right_align(conUl, num_len);
}


void    print_char(char ch, int *opt)
{
    int space_len;

    if (1 < opt[width])
        space_len = opt[width] - 1;
    else
        space_len = 0;
    if (opt[minus])
    {
        write(1, &ch, 1);
        while (space_len--)
            write(1, " ", 1);
    }
    else
    {
        while (space_len--)
            write(1, " ", 1);
        write(1, &ch, 1);
    }
}

void    print_string(char *str, int *opt)
{
    int str_len;
    int space_len;

    str_len = ft_strlen(str);
    if (str_len < opt[width])
        space_len = opt[width] - str_len;
    else
        space_len = 0;
    if (opt[minus])
    {
        write(1, str, str_len);
        while (space_len--)
            write(1, " ", 1);
    }
    else
    {
        while (space_len--)
            write(1, " ", 1);
        write(1, str, str_len);
    }
}




